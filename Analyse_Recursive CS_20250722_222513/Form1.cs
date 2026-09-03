using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using VB = Microsoft.VisualBasic;
using Microsoft.VisualBasic;
using Microsoft.VisualBasic.CompilerServices;
using System.ComponentModel.DataAnnotations;
#pragma warning disable CS8600 // Conversion de littéral ayant une valeur null ou d'une éventuelle valeur null en type non-nullable.
#pragma warning disable CS8601 // Existence possible d'une assignation de référence null.
#pragma warning disable CS8603 // Existence possible d'un retour de référence null.
namespace Analyse_Recursive_CS
{
        public struct BrowseInfo
        {
            public int lngHwnd;
            public int pIDLRoot;
            public int pszDisplayName;
            public int lpszTitle;
            public int ulFlags;
            public int lpfnCallback;
            public int lParam;
            public int iImage;
        }
        public struct FILETIME
        {
            public int dwLowDateTime;
            public int dwHighDateTime;
        }
        public enum ListPaths
        {
            PathsAndFilenames = 1,
            FilenamesOnly = 2,
            PathsOnly = 3
        }
    public partial class Form1 : Form
    {
        public Form1() => InitializeComponent();
        //internal Collection colInPaths;
        //internal Collection colOutpaths;
        //internal string sInputPath;
        //internal string sOutputPath;
        //internal string sInputPath2;
        //internal string sOutputPath2;
        //internal int lTotalProcess;
        //internal string SearchPath, FindStr;
        //internal int FileSize;
        internal short NumFiles=-1, NumDirs=-1;
        //internal string AppStringName;
        [Required]internal Collection cTempCollection;
        internal string dWork=string.Empty;
        [DllImport("Kernel32", EntryPoint = "FindFirstFileA")] internal static extern int FindFirstFile(string lpFileName, ref WIN32_FIND_DATA lpFindFileData);
        [DllImport("Kernel32", EntryPoint = "FindNextFileA")] internal static extern int FindNextFile(int hFindFile, ref WIN32_FIND_DATA lpFindFileData);
        [DllImport("Kernel32", EntryPoint = "GetFileAttributesA")] internal static extern int GetFileAttributes(string lpFileName);
        [DllImport("Kernel32")] internal static extern int FindClose(int hFindFile);
        [DllImport("ole32.dll")] internal static extern void CoTaskMemFree(int hMem);
        [DllImport("Kernel32", EntryPoint = "lstrcatA")] internal static extern int lstrcat(string lpString1, string lpString2);
        [DllImport("shell32")] internal static extern int SHBrowseForFolder(ref BrowseInfo lpbi);
        [DllImport("shell32")] internal static extern int SHGetPathFromIDList(int pidList, string lpBuffer);
        internal ListPaths ListSelected;
           internal const short MAX_PATH = 260;
        internal const int MAXDWORD = 0xFFFF;
        internal const short INVALID_HANDLE_VALUE = -1;
        internal const int FILE_ATTRIBUTE_ARCHIVE = 0x20;
        internal const int FILE_ATTRIBUTE_DIRECTORY = 0x10;
        internal const int FILE_ATTRIBUTE_HIDDEN = 0x2;
        internal const int FILE_ATTRIBUTE_NORMAL = 0x80;
        internal const int FILE_ATTRIBUTE_READONLY = 0x1;
        internal const int FILE_ATTRIBUTE_SYSTEM = 0x4;
        internal const int FILE_ATTRIBUTE_TEMPORARY = 0x100;
        internal const short BIF_RETURNONLYFSDIRS = 1;
     internal struct WIN32_FIND_DATA
        {
            public int dwFileAttributes;
            public FILETIME ftCreationTime;
            public FILETIME ftLastAccessTime;
            public FILETIME ftLastWriteTime;
            public int nFileSizeHigh;
            public int nFileSizeLow;
            public int dwReserved0;
            public int dwReserved1;

            [VBFixedString(MAX_PATH)]
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_PATH)]
            public char[] cFileName;

            [VBFixedString(14)]
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 14)]
            public char[] cAlternate;
        }

        internal string BrowseForFolder(int lngHwnd, string strPrompt) 
        {
            try
            {
                short intNull;
                int lngIDList, lngResult;
                var strPath = default(string);
                var udtBI = default(BrowseInfo);
                // Set API properties (housed in a UDT)
                {
                    ref var withBlock = ref udtBI;
                    withBlock.lngHwnd = lngHwnd;
                    string arglpString2 = "";
                    withBlock.lpszTitle = Form1.lstrcat(strPrompt, arglpString2);
                    withBlock.ulFlags = BIF_RETURNONLYFSDIRS;
                }
                lngIDList = SHBrowseForFolder(ref udtBI);
                if (lngIDList != 0)
                {
                    strPath = new string('\0', MAX_PATH);
                    lngResult = Form1.SHGetPathFromIDList(lngIDList, strPath);
                    CoTaskMemFree(lngIDList);
                    intNull = (short)Strings.InStr(strPath, Constants.vbNullChar);
                    if (intNull > 0)
                    {
                        strPath = Strings.Left(strPath, intNull - 1);
                    }
                }
                return strPath;
            }
            catch
            {
                return string.Empty; 
            }

        }
        public string StripNulls(ref string OriginalStr)
        {
            string StripNullsRet = default;
            if (Strings.InStr(OriginalStr, "\0") > 0)
            {
                OriginalStr = Strings.Left(OriginalStr, Strings.InStr(OriginalStr, "\0") - 1);
            }
            StripNullsRet = OriginalStr;
            return StripNullsRet;
        }
        public object FindFilesAPI(string Path, string SearchStr, short FileCount, short DirCount)
        {
            object FindFilesAPIRet = default;


            string FileName; // Walking filename variable...
            string DirName; // SubDirectory Name
            string[] dirNames; // Buffer for directory name entries
            short nDir; // Number of directories in this path
            short i; // For-loop counter...
            int hSearch; // Search Handle
            var WFD = default(WIN32_FIND_DATA);
            short Cont;
            if (Strings.Right(Path, 1) != @"\")
                Path = Path + @"\";
            // Search for subdirectories.
            nDir = 0;
            dirNames = new string[(nDir + 1)];
            Cont = Conversions.ToShort(true);
            string arglpFileName = Path + "*";
            hSearch = Form1.FindFirstFile(arglpFileName, ref WFD);
            if (hSearch != INVALID_HANDLE_VALUE)
            {
                while (Cont > 0)
                {
                    string argOriginalStr = Conversions.ToString(WFD.cFileName);
                    DirName = StripNulls(ref argOriginalStr);
                    WFD.cFileName = argOriginalStr.ToCharArray();
                    if (DirName != "." & DirName != "..")
                    {
                        string arglpFileName1 = Path + DirName;
                        if (Conversions.ToBoolean(Form1.GetFileAttributes(arglpFileName1) & FILE_ATTRIBUTE_DIRECTORY))
                        {
                            if (Strings.InStr(1, Path + DirName, "Processed") == 0)
                            {
                                dirNames[nDir] = DirName;
                                dossiers.Items.Add(Path + DirName);
                                DirCount = (short)(DirCount + 1);
                                nDir = (short)(nDir + 1);
                                Array.Resize(ref dirNames, nDir + 1);
                            }
                        }
                    }
                    Cont = (short)FindNextFile(hSearch, ref WFD);
                }
                Cont = (short)FindClose(hSearch);
            }
            string arglpFileName2 = Path + SearchStr;
            hSearch = Form1.FindFirstFile(arglpFileName2, ref WFD);
            Cont = Conversions.ToShort(true);
            if (hSearch != INVALID_HANDLE_VALUE)
            {
                while (Cont > 0)
                {
                    string argOriginalStr1 = Conversions.ToString(WFD.cFileName);
                    FileName = StripNulls(ref argOriginalStr1);
                    WFD.cFileName = argOriginalStr1.ToCharArray();
                    if (FileName != "." & FileName != "..")
                    {
                        FindFilesAPIRet = Operators.AddObject(Operators.AddObject(FindFilesAPIRet, WFD.nFileSizeHigh * MAXDWORD), WFD.nFileSizeLow);
                        FileCount = (short)(FileCount + 1);

                        if (Strings.InStr(1, Path + FileName, "SYSTEM FILES") != 0)
                        {
                        }
                        else
                        {
                            cTempCollection.Add(Path + FileName);
                            List1.Items.Add(Path + FileName);
                        }
                    }
                    Cont = (short)FindNextFile(hSearch, ref WFD); // Get next file
                }
                Cont = (short)FindClose(hSearch);
            }
            if (nDir > 0)
            {
                for (i = 0; i <= (short)(nDir - 1); i++)
                    FindFilesAPIRet = Operators.AddObject(FindFilesAPIRet, FindFilesAPI(Path + dirNames[i] + @"\", SearchStr, FileCount, DirCount));
            }

            return FindFilesAPIRet;
        }

        internal Collection DoFileSystemSearch(string sPath, string sFilter, ListPaths ListAction)
        {
            Collection DoFileSystemSearchRet = null;
            ListSelected = ListAction;
            cTempCollection = new Collection();
            FindFilesAPI(sPath, sFilter, NumFiles, NumDirs);
            DoFileSystemSearchRet = cTempCollection;
            Interaction.MsgBox(cTempCollection.Count, MsgBoxStyle.Information, "Collection");
            return DoFileSystemSearchRet;

        }
        internal void Command3_Click(object sender, EventArgs e) => Environment.Exit(0);
        internal void Command2_Click(object sender, EventArgs e)
        {
            int x;
            FileSystem.FileOpen(1, dWork + @"\dossiers.inf", OpenMode.Output);
            FileSystem.PrintLine(1, "[Folder]");
            for (x = 0; x <= dossiers.Items.Count - 1; x++)
                FileSystem.PrintLine(1, $"{x}={dossiers}");
            FileSystem.FileClose(1);
            FileSystem.FileOpen(1, dWork + @"\fichiers.inf", OpenMode.Output);
            FileSystem.PrintLine(1, "[Files]");
            for (x = 0; x <= List1.Items.Count - 1; x++)
                FileSystem.PrintLine(1, $"{x}={List1.Items[x].ToString()}");
            FileSystem.FileClose(1);
        }
        internal void Command1_Click(object sender, EventArgs e)
        {
            dWork = BrowseForFolder(0, Command1.Text);
            var cfList = new Collection();
            DoFileSystemSearch(dWork, "*.*", ListPaths.PathsAndFilenames);
        }
    }
}