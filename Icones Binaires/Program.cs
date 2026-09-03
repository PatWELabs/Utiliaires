using System.Collections.Concurrent;
using System.Diagnostics;
using System.Security.Cryptography;
using System.Text;

namespace IconesBinaires
{
    internal class Program
    {
        static async Task<int> Main(string[] args)
        {
            Console.OutputEncoding = Encoding.UTF8;
            if (args.Length < 2)
            {
                Console.WriteLine("Utilisation : IconesBinaires <dossierSource> <dossierDestination>");
                Console.WriteLine("Exemple   : IconesBinaires C:\\ C:\\IconsExport");
                return 1;
            }
            string sourceRoot = args[0];
            string outputRoot = args[1];
            if (!Directory.Exists(sourceRoot)){  Console.WriteLine($"Dossier source introuvable : {sourceRoot}"); return 1; }
            Directory.CreateDirectory(outputRoot);
            Console.WriteLine($"Source      : {sourceRoot}");
            Console.WriteLine($"Destination : {outputRoot}");
            Console.WriteLine();
            var scanner = new AnalyseurFichier(new[]{".exe", ".dll", ".ico"});
            var iconExtractor = new ExtracteurIcones();
            var iconHasher = new HasheurIcone();
            var iconSaver = new SauvegardeIcone(outputRoot);
            var uniqueHashes = new ConcurrentDictionary<string, bool>();
            var files = scanner.EnumerateFiles(sourceRoot);
            int totalFiles = 0;
            int filesWithIcons = 0;
            int iconsSaved = 0;
            var swTotal = Stopwatch.StartNew();
            await Parallel.ForEachAsync(files, new ParallelOptions{MaxDegreeOfParallelism = Environment.ProcessorCount}, async (filePath, _) =>
            {
                try
                {
                    Interlocked.Increment(ref totalFiles);
                    var extractedIcons = iconExtractor.ExtraireIcones(filePath);
                    if (extractedIcons.Count == 0) return;
                    Interlocked.Increment(ref filesWithIcons);
                    foreach (var iconInfo in extractedIcons)
                    {
                        using var bmp = iconInfo.Bitmap;
                        // Hash basé sur les pixels pour éviter doublons
                        string hash = iconHasher.CalculeHash(bmp);
                        if (uniqueHashes.TryAdd(hash, true))
                        {
                            string baseName = iconSaver.GenererNomBasique(filePath, iconInfo.Size);
                            await iconSaver.SauvegardeIconeAsynchrone(bmp, baseName);
                            Interlocked.Increment(ref iconsSaved);
                        }
                    }
                }
                catch (Exception ex){Console.WriteLine($"Erreur fichier {filePath}: {ex.Message}");}
            });
            swTotal.Stop();
            Console.WriteLine();
            Console.WriteLine("Terminé.");
            Console.WriteLine($"Fichiers scannés       : {totalFiles}");
            Console.WriteLine($"Fichiers avec icônes   : {filesWithIcons}");
            Console.WriteLine($"Icônes uniques sauvées : {iconsSaved}");
            Console.WriteLine($"Durée totale           : {swTotal.Elapsed}");
            return 0;
        }
    }
    /// <summary>
    /// Parcours récursif des fichiers avec filtre sur les extensions.
    /// </summary>
    internal class AnalyseurFichier
    {
        private readonly HashSet<string> _extensions;
        public AnalyseurFichier(IEnumerable<string> extensions){_extensions = new HashSet<string>(extensions.Select(e => e.ToLowerInvariant()), StringComparer.OrdinalIgnoreCase);}
        public IEnumerable<string> EnumerateFiles(string root)
        {
            var dirs = new Stack<string>();
            dirs.Push(root);
            while (dirs.Count > 0)
            {
                string currentDir = dirs.Pop();
                string[] subDirs;
                try { subDirs = Directory.GetDirectories(currentDir); }
                catch{continue;}
                foreach (var d in subDirs) dirs.Push(d);
                string[] files;
                try{files = Directory.GetFiles(currentDir);}
                catch{continue;}
                foreach (var file in files)
                {
                    string ext = Path.GetExtension(file).ToLowerInvariant();
                    if (_extensions.Contains(ext)) yield return file;
                }
            }
        }
    }
    internal sealed class ExtraireInformationsIcone
    {
        public Bitmap Bitmap { get; }
        public Size Size { get; }
        public ExtraireInformationsIcone(Bitmap bitmap, Size size)
        {
            Bitmap = bitmap;
            Size = size;
        }
    }
    internal class ExtracteurIcones
    {
        private static readonly Size[] DimensionsValides =
        {
            new(256, 256),
            new (128, 128),
            new (64, 64),
            new (48, 48),
            new (32, 32),
            new (16, 16)
        };
        public List<ExtraireInformationsIcone> ExtraireIcones(string filePath)
        {
            string ext = Path.GetExtension(filePath).ToLowerInvariant();
            if (ext == ".ico") return ExtraireDepuisIcone(filePath);
            if (ext == ".exe" || ext == ".dll")return ExtraireDepuisExecutable(filePath);
            return [];
        }
        private List<ExtraireInformationsIcone> ExtraireDepuisIcone(string filePath)
        {
            var list = new List<ExtraireInformationsIcone>();
            try
            {
                using Icon icon = new Icon(filePath);
                using Bitmap bmp = icon.ToBitmap();
                var bestSize = SelectionMeilleurTaille(bmp.Size);
                using Bitmap resized = AjusterAuBesoin(bmp, bestSize);
                list.Add(new ExtraireInformationsIcone((Bitmap)resized.Clone(), resized.Size));
            }
            catch(Exception ex) { Console.WriteLine(ex.Message);}
            return list;
        }
        private List<ExtraireInformationsIcone> ExtraireDepuisExecutable(string filePath)
        {
            var list = new List<ExtraireInformationsIcone>();
            try
            {
                using Icon? associatedIcon = Icon.ExtractAssociatedIcon(filePath);
                if (associatedIcon == null) return list;
                using Bitmap bmp = associatedIcon.ToBitmap();
                var bestSize = SelectionMeilleurTaille(bmp.Size);
                using Bitmap resized = AjusterAuBesoin(bmp, bestSize);
                list.Add(new ExtraireInformationsIcone((Bitmap)resized.Clone(), resized.Size));
            }
            catch(Exception ex){Console.WriteLine(ex.Message);}
            return list;
        }
        private static Size SelectionMeilleurTaille(Size original)
        {
            foreach (var size in DimensionsValides)
            {
                if (original.Width >= size.Width && original.Height >= size.Height)return size;
            }
            return original;
        }
        private static Bitmap AjusterAuBesoin(Bitmap source, Size targetSize)
        {
            if (source.Width == targetSize.Width && source.Height == targetSize.Height) return (Bitmap)source.Clone();
            var dest = new Bitmap(targetSize.Width, targetSize.Height, source.PixelFormat);
            dest.SetResolution(source.HorizontalResolution, source.VerticalResolution);
            using (var g = Graphics.FromImage(dest))
            {
                g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
                g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
                g.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.HighQuality;
                g.CompositingQuality = System.Drawing.Drawing2D.CompositingQuality.HighQuality;
                g.DrawImage(source, new Rectangle(Point.Empty, targetSize));
            }
            return dest;
        }
    }
    internal class HasheurIcone
    {
        public string CalculeHash(Bitmap bmp)
        {
            using var normalized = new Bitmap(bmp.Width, bmp.Height, System.Drawing.Imaging.PixelFormat.Format32bppArgb);
            normalized.SetResolution(bmp.HorizontalResolution, bmp.VerticalResolution);
            using (var g = Graphics.FromImage(normalized)){g.DrawImageUnscaled(bmp, 0, 0);}
            var data = normalized.LockBits(new Rectangle(0, 0, normalized.Width, normalized.Height),System.Drawing.Imaging.ImageLockMode.ReadOnly,normalized.PixelFormat);
            try
            {
                int bytes = Math.Abs(data.Stride) * data.Height;
                byte[] buffer = new byte[bytes];
                System.Runtime.InteropServices.Marshal.Copy(data.Scan0, buffer, 0, bytes);
                using var sha = SHA256.Create();
                byte[] hashBytes = sha.ComputeHash(buffer);
                return Convert.ToHexString(hashBytes);
            }
            finally{normalized.UnlockBits(data);}
        }
    }
    internal class SauvegardeIcone
    {
        private readonly string _outputRoot;
        public SauvegardeIcone(string outputRoot) => _outputRoot = outputRoot;
        public string GenererNomBasique(string filePath, Size size)
        {
            string fileName = Path.GetFileNameWithoutExtension(filePath);
            string safeName = GenererNomSur(fileName);
            return $"{safeName}_{size.Width}x{size.Height}";
        }
        public async Task SauvegardeIconeAsynchrone(Bitmap bitmap, string baseName)
        {
            string subFolder = Path.Combine(_outputRoot, $"{bitmap.Width}x{bitmap.Height}");
            Directory.CreateDirectory(subFolder);
            string filePath = Path.Combine(subFolder, baseName + ".png");
            var counter = 1;
            string finalPath = filePath;
            while (File.Exists(finalPath)){finalPath = Path.Combine(subFolder, $"{baseName}_{counter}.png");counter++;}
            using var ms = new MemoryStream();
            bitmap.Save(ms, System.Drawing.Imaging.ImageFormat.Png);
            ms.Position = 0;
            using var fs = new FileStream(finalPath, FileMode.CreateNew, FileAccess.Write, FileShare.None);
            await ms.CopyToAsync(fs);
        }
        private static string GenererNomSur(string name)
        {
            foreach (char c in Path.GetInvalidFileNameChars()){name = name.Replace(c, '_');}
            return name;
        }
    }
}

