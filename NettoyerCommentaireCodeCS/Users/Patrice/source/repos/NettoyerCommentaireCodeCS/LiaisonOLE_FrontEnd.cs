using ADODB;
using System;
using System.IO;
#pragma warning disable CS8618 // Un champ non-nullable doit contenir une valeur non-null lors de la fermeture du constructeur. Envisagez de déclarer le champ comme nullable.
#pragma warning disable CS0649

namespace PWE.Serveur.AutoGRB
{
public class DR_ApercuProjet
{
public static string lblNumero;
public static string lblClient;
public static string lblDescription;
public static string lblDate;
public static string lblForfaitMecSoum;
public static string lblForfaitElecSoum;
public static string lblTotalForfaitSoum;
public static string lblForfaitElecProj;
public static string lblForfaitMecProj;
public static string lblTotalForfaitProj;
public static string lblHeuresElecTotalSoum;
public static string lblHeuresMecTotalSoum;
public static string lblTotalHeuresSoum;
public static string lblGrandTotalSoum;
public static string lblTotalElecSoum;
public static string lblTotalMecSoum;
public static string lblTotalHeuresProj;
public static string lblHeuresElecTotalProj;
public static string lblHeuresMecTotalProj;
public static string lblGrandTotalProj;
public static string lblTotalElecProj;
public static string lblTotalMecProj;
public static string lblProfitSoum;
public static string lblProfitProj;
public static string lblProjetElec;
public static string lblArgentElecDessinSoum;
public static string lblHeuresElecDessinSoum;
public static string lblArgentElecFabricationSoum;
public static string lblHeuresElecFabricationSoum;
public static string lblArgentElecAssemblageSoum;
public static string lblHeuresElecAssemblageSoum;
public static string lblArgentElecProgInterfaceSoum;
public static string lblHeuresElecProgInterfaceSoum;
public static string lblArgentElecProgAutomateSoum;
public static string lblHeuresElecProgAutomateSoum;
public static string lblArgentElecProgRobotSoum;
public static string lblHeuresElecProgRobotSoum;
public static string lblHeuresElecVisionSoum;
public static string lblArgentElecVisionSoum;
public static string lblHeuresElecTestSoum;
public static string lblArgentElecTestSoum;
public static string lblArgentElecInstallationSoum;
public static string lblHeuresElecInstallationSoum;
public static string lblHeuresElecMiseServiceSoum;
public static string lblArgentElecMiseServiceSoum;
public static string lblHeuresElecFormationSoum;
public static string lblArgentElecFormationSoum;
public static string lblHeuresElecGestionSoum;
public static string lblArgentElecGestionSoum;
public static string lblHeuresElecShippingSoum;
public static string lblArgentElecShippingSoum;
public static string lblPiecesElecSoum;
public static string lblImprevuElecSoum;
public static string lblAutresElecSoum;
public static string lblArgentElecAssemblageProj;
public static string lblHeuresElecDessinProj;
public static string lblArgentElecDessinProj;
public static string lblHeuresElecFabricationProj;
public static string lblArgentElecFabricationProj;
public static string lblHeuresElecAssemblageProj;
public static string lblHeuresElecProgInterfaceProj;
public static string lblArgentElecProgInterfaceProj;
public static string lblArgentElecProgAutomateProj;
public static string lblHeuresElecProgAutomateProj;
public static string lblHeuresElecProgRobotProj;
public static string lblArgentElecProgRobotProj;
public static string lblHeuresElecVisionProj;
public static string lblArgentElecVisionProj;
public static string lblHeuresElecTestProj;
public static string lblArgentElecTestProj;
public static string lblArgentElecInstallationProj;
public static string lblHeuresElecInstallationProj;
public static string lblHeuresElecMiseServiceProj;
public static string lblArgentElecMiseServiceProj;
public static string lblHeuresElecFormationProj;
public static string lblArgentElecFormationProj;
public static string lblHeuresElecGestionProj;
public static string lblArgentElecGestionProj;
public static string lblHeuresElecShippingProj;
public static string lblArgentElecShippingProj;
public static string lblHeuresElecRechercheProj;
public static string lblArgentElecRechercheProj;
public static string lblImprevuElecProj;
public static string lblPiecesElecProj;
public static string lblAutresElecProj;
public static string lblArgentElecTotalSoum;
public static string lblArgentElecTotalProj;
public static string lblHeuresMecDessinSoum;
public static string lblArgentMecDessinSoum;
public static string lblHeuresMecCoupeSoum;
public static string lblArgentMecCoupeSoum;
public static string lblHeuresMecMachinageSoum;
public static string lblArgentMecMachinageSoum;
public static string lblHeuresMecSoudureSoum;
public static string lblArgentMecSoudureSoum;
public static string lblHeuresMecAssemblageSoum;
public static string lblArgentMecAssemblageSoum;
public static string lblHeuresMecPeintureSoum;
public static string lblArgentMecPeintureSoum;
public static string lblHeuresMecTestSoum;
public static string lblArgentMecTestSoum;
public static string lblHeuresMecInstallationSoum;
public static string lblArgentMecInstallationSoum;
public static string lblHeuresMecFormationSoum;
public static string lblArgentMecFormationSoum;
public static string lblHeuresMecGestionSoum;
public static string lblArgentMecGestionSoum;
public static string lblHeuresMecShippingSoum;
public static string lblArgentMecShippingSoum;
public static string lblPiecesMecSoum;
public static string lblImprevuMecSoum;
public static string lblAutresMecSoum;
public static string lblProjetMec;
public static string lblHeuresMecDessinProj;
public static string lblArgentMecDessinProj;
public static string lblHeuresMecCoupeProj;
public static string lblArgentMecCoupeProj;
public static string lblArgentMecMachinageProj;
public static string lblHeuresMecMachinageProj;
public static string lblHeuresMecSoudureProj;
public static string lblArgentMecSoudureProj;
public static string lblHeuresMecAssemblageProj;
public static string lblArgentMecAssemblageProj;
public static string lblHeuresMecPeintureProj;
public static string lblArgentMecPeintureProj;
public static string lblHeuresMecTestProj;
public static string lblArgentMecTestProj;
public static string lblHeuresMecInstallationProj;
public static string lblArgentMecInstallationProj;
public static string lblHeuresMecFormationProj;
public static string lblArgentMecFormationProj;
public static string lblHeuresMecGestionProj;
public static string lblArgentMecGestionProj;
public static string lblArgentMecShippingProj;
public static string lblHeuresMecShippingProj;
public static string lblHeuresMecRechercheProj;
public static string lblArgentMecRechercheProj;
public static string lblPiecesMecProj;
public static string lblImprevuMecProj;
public static string lblAutresMecProj;
public static string lblArgentMecTotalSoum;
public static string lblArgentMecTotalProj;
public static string lblTitreRapport;
public static string lblTitreNoProjet;
public static string lblTitreProj;
public static string lblTitreClient;
public static string lblTitreDescription;
public static string lblTitreDate;
public static string lblTitreSoum;
public static string lblTitreHeuresSoum;
public static string lblTitreArgentSoum;
public static string lblTitreHeuresProj;
public static string lblTitreArgentProj;
public static string lblTitreRevenus;
public static string lblTitreForfaitElec;
public static string lblTitreForfaitMec;
public static string lblTitreTotalForfait;
public static string lblTitreDepenses;
public static string lblTitreTempsElec;
public static string lblTitreTempsElecDessin;
public static string lblTitreTempsElecFabrication;
public static string lblTitreTempsElecAssemblage;
public static string lblTitreTempsElecProgInterface;
public static string lblTitreTempsElecProgAutomate;
public static string lblTitreTempsElecProgRobot;
public static string lblTitreTempsElecVision;
public static string lblTitreTempsElecTest;
public static string lblTitreTempsElecInstallation;
public static string lblTitreTempsElecMiseService;
public static string lblTitreTempsElecFormation;
public static string lblTitreTempsElecGestion;
public static string lblTitreTempsElecShipping;
public static string lblTitreTempsElecTotal;
public static string lblHeuresElecTotalProj0;
public static string lblTotalElecProj0;
public static string lblTitrePiecesElec;
public static string lblTitreImprevuElec;
public static string lblTitreAutresElec;
public static string lblTitreTotalElec;
public static string lblTotalElecSoum0;
public static string lblTotalHeuresProj0;
public static string lblTitreTempsMec;
public static string lblTitreTempsMecDessin;
public static string lblTitreTempsMecCoupe;
public static string lblTitreTempsMecMachinage;
public static string lblTitreTempsMecSoudure;
public static string lblTitreTempsMecAssemblage;
public static string lblTitreTempsMecPeinture;
public static string lblTitreTempsMecTest;
public static string lblTitreTempsMecInstallation;
public static string lblTitreTempsMecFormation;
public static string lblTitreTempsMecGestion;
public static string lblTitreTempsMecShipping;
public static string Label2;
public static string lblTitreTempsMecTotal;
public static string lblTitrePiecesMec;
public static string lblTitreImprevuMec;
public static string lblTitreAutresMec;
public static string lblTitreTotalMec;
public static string lblTitreTotal;
public static string lblTitreProfitTotal;
}
public class DR_BackOrder
{
internal static string blTitre;
internal static string blTitreProjetAchat;
internal static string blDate;
internal static string blProjetAchat;
internal static string blTitreNoProjet;
internal static string xtNoProjAchat;
internal static string xtNoItem;
internal static string Impression;
internal static string lblTitre;
internal static string Label5;
internal static string lblDate;
internal static string lblTitreProjetAchat;
internal static string lblProjetAchat;
internal static string lblTitreNoProjet;
internal static string lblTitreQuantite;
internal static string lblTitreNoItem;
internal static string lblTitreDescription;
internal static string lblTitreFournisseur;
internal static string Label2;
internal static string Label3;
internal static string txtNoProjAchat;
internal static string Text1;
internal static string txtNoItem;
internal static string Text3;
internal static string Text4;
internal static string Text6;
internal static string Text5;
internal static string Qte;
internal static string Description;
internal static string Fournisseur;
internal static string DateCommande;
internal static string DateRequise;
public static Recordset DataSource;
public static bool Visible;
public static bool Orientation;
}
public class DR_BonLivraison
{
public static bool Orientation;
public static string Controls34;
public static string Controls35;
public static string Controls36;
public static string Controls37;
public static string Controls44;
public static string Controls45;
public static string Controls38;
public static string Controls39;
public static string Controls40;
public static string Controls46;
public static string Controls47;
public static string Controls41;
public static string Controls42;
public static string Controls43;
}
public class DR_BonTravail
{
public static string lblTitre;
public static string Label4;
public static string lblClient;
public static string Label7;
public static string lblFacture;
public static string Label5;
public static string lblContact;
public static string Label6;
public static string lblTelephone;
public static string Label33;
public static string lblFax;
public static string Label8;
public static string lblRepresentantGRB;
public static string Label12;
public static string lblBonTravail;
public static string Label9;
public static string lblNoCommandeClient;
public static string Label10;
public static string lblDateCommande;
public static string Label13;
public static string Label1;
public static string Label11;
public static string lblDateHeure;
public static string Label14;
public static string Label15;
public static string Label16;
public static string Label2;
public static string Label3;
public static string Label22;
public static string Label23;
public static string Label29;
public static string Label30;
public static string Label31;
public static string Label34;
public static string Label35;
public static string Label36;
public static string Label37;
public static string Label32;
public static string Label24;
public static string Label42;
public static string Label17;
public static string Label26;
public static string Label18;
public static string Label19;
public static string Label20;
public static string Label21;
public static bool Orientation;
}
public class DR_Client
{
public static string EnTeteAdresse;
public static string EnTeteTelFax;
public static string Label3;
public static string Label7;
public static string Label29;
public static string TextBox1;
public static string TextBox2;
public static string Label1;
public static string lblDate;
public static string TextBox3;
public static string Label33;
public static string lblDateOuverture;
public static string Label34;
public static string lblDateDue;
public static string Label35;
public static string TextBox4;
public static string lblClient;
public static string lblContact;
public static string Label38;
public static string TextBox5;
public static string lblProjet;
public static string Label36;
public static string lblTel;
public static string Label37;
public static string lblFax;
public static string Label30;
public static string Label31;
public static string Label32;
public static string Label8;
public static string TextBox6;
public static string TextBox7;
public static string TextBox8;
public static string Label9;
public static string TextBox9;
public static string TextBox10;
public static string TextBox11;
public static string Label10;
public static string TextBox12;
public static string TextBox13;
public static string TextBox14;
public static string Label11;
public static string TextBox15;
public static string TextBox16;
public static string TextBox17;
public static string Label12;
public static string TextBox18;
public static string TextBox19;
public static string TextBox20;
public static string Label13;
public static string TextBox21;
public static string TextBox22;
public static string TextBox23;
public static string Label14;
public static string TextBox24;
public static string TextBox25;
public static string TextBox26;
public static string Label15;
public static string TextBox27;
public static string TextBox28;
public static string TextBox29;
public static string Label16;
public static string TextBox30;
public static string TextBox31;
public static string TextBox32;
public static string Label17;
public static string TextBox33;
public static string TextBox34;
public static string TextBox35;
public static string Label18;
public static string TextBox36;
public static string TextBox37;
public static string TextBox38;
public static string Label19;
public static string TextBox39;
public static string TextBox40;
public static string TextBox41;
public static string Label20;
public static string TextBox42;
public static string TextBox43;
public static string TextBox44;
public static string Label21;
public static string TextBox45;
public static string TextBox46;
public static string TextBox47;
public static string Label22;
public static string TextBox48;
public static string TextBox49;
public static string TextBox50;
public static string lblUser;
public static string lblNoSoum;
public static string lblNoProj;
public static string lblProjetNom;
public static bool Orientation;
}
public class DR_Commande
{
public static string EnTeteAdresse;
public static string EnTeteTelFax;
public static string lblTitreCommande;
public static string lblTitreFournisseur;
public static string lblFournisseur;
public static string lblTitreNoSoum;
public static string lblNoSoum;
public static string lblTitreBC;
public static string lblNoBC;
public static string lblTitreContact;
public static string lblContact;
public static string lblTitreTel;
public static string lblTel;
public static string lbltitredate;
public static string lblDate;
public static string lbltitredatereq;
public static string lblDateRequise;
public static string lblTitreFax;
public static string lblTitreTransport;
public static string lblFax;
public static string lblTransport;
public static string lbltitrecompar;
public static string lblTitrePage;
public static string lblCommandePar;
public static string lblPage;
public static string lblPiedPage;
public static string lblCSA;
public static string lbltitrecommentaire;
public static string lblCommentaire;
public static string lbltitretotalfin;
public static string lblTotalFin;
public static string lblCopieCredit;
public static string lblAdresse;
public static string lbltitredescription;
public static string lbltitreescompte;
public static string lbltitremanufact;
public static string lbltitrePiece;
public static string lbltitreprix;
public static string lbltitreqte;
public static string lbltitretotal;
public static string lbltypeprix;
public static bool Orientation = WebGRB2024.Program.isLandscape;
public static string Title;
}
public class DR_CommandeParcel
{
public static string EnTeteAdresse;
public static string EnTeteTelFax;
public static string Label3;
public static string Label4;
public static string Label14;
public static string lblgrb;
public static string lblcompagnie;
public static string lbladresse;
public static string lblpays;
public static string Label5;
public static string lblreminder;
public static string Label7;
public static string Label8;
public static string Label11;
public static string Label9;
public static string Label12;
public static string Label10;
public static string lblassist;
public static string lblUser;
public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public class DR_CommandeRecue
{
public static dynamic lblfournisseur;
public static dynamic lblprojet;
public static dynamic lbldatereq;
public static bool Orientation = !WebGRB2024.Program.isLandscape;
public static Recordset DataSource;
}
public class DR_Conception
{
public static string EnTeteAdresse;
public static string EnTeteTelFax;
public static string Controls3;
public static string Controls7;
public static string Controls7p;
public static string Controls29;
public static string Controls43;
public static string Controls1;
public static string Controls46;
public static string Controls2;
public static string Controls44;
public static string Controls33;
public static string Controls45;
public static string Controls34;
public static string TextBox1;
public static string Controls35;
public static string TextBox2;
public static string Controls4;
public static string Controls39;
public static string Controls5;
public static string Controls40;
public static string Controls38;
public static string TextBox3;
public static string Controls6;
public static string Controls47;
public static string Controls36;
public static string Controls41;
public static string Controls37;
public static string Controls42;
public static string Controls30;
public static string Controls31;
public static string Controls32;
public static string Controls8;
public static string Controls9;
public static string Controls10;
public static string Controls11;
public static string Controls12;
public static string Controls13;
public static string Controls14;
public static string Controls15;
public static string Controls16;
public static string Controls17;
public static string Controls18;
public static string Controls19;
public static string Controls20;
public static string Controls21;
public static string Controls22;
public static string Controls23;
public static string Controls24;
public static string Controls25;
public static string Controls26;
public static string Controls27;
public static string Controls28;
private static object Impression;
public static bool Orientation;
public static string Controls90;
public static string Controls91;
public static string Controls92;
public static string Controls93;
public static string Controls94;
public static string Controls95;
public static string Controls96;
public static string Controls97;
public static string Controls98;
public static string Controls99;
public static string EnTeteLogo;
public void CreerPage()
{
StreamWriter sw = new StreamWriter($"\\\\developpement\\D$\\CacheWeb\\DR_Conception_{WebGRB2024.Program.IdNoEmploye}_{DateTime.Now.ToShortDateString()}.html");
sw.Write($"<!DOCTYPE html><html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta http-equiv=\"Content-Type\" " +
$"content=\"text/html; charset=utf-8\" /><title>{DR_Conception.EnTeteAdresse}</title></head><body>" +
$"<form ><div class=\"aspNetHidden\"></div><div><div {DR_Conception.Impression}><table align=\"right\">" +
$"<tr align=\"center\"><td><img alt=\"{DR_Conception.EnTeteLogo}\" src=\"images/logo%20GRB-inc.2.bmp\" /></td></tr>" +
$"<tr align=\"center\"><td>149, rue Pierre Paradis, <br />St-Alphonse-de-Granby, QC J0E 2A4</td></tr>" +
$"<tr align=\"center\"><td>Tel: (450) 372-0021  Fax: (450) 372-3860</td></tr></table><br />");
sw.Write($"<table><tr><td class=\"text-center\" colspan=\"3\"><br /><span {DR_Conception.Controls3} style=\"font-size:Larger;\">" +
$"CONCEPTION</span></td><td>    <span {DR_Conception.Controls7}>Soumission: </span><br />" +
$"<span {DR_Conception.Controls7p}>Projet #: </span></td><td><span {DR_Conception.Controls29}></span>" +
$"<br /><span {DR_Conception.Controls43}></span></td><td><span {DR_Conception.Controls1}>" +
$"Date: </span></td><td><span {DR_Conception.Controls46}></span></td></tr><tr><td rowspan=\"2\">" +
$"<span {DR_Conception.Controls2}>Projet/Nom: </span></td><td colspan=\"6\">" +
$"<span {DR_Conception.Controls44} style=\"display:inline-block;width:100%;\"></span></td></tr><tr><td>" +
$"<span {DR_Conception.Controls33}>Date d'ouverture: </span></td><td>" +
$"<span {DR_Conception.Controls45}></span></td><td>" +
$"<span {DR_Conception.Controls34}>Date du: </span></td><td>" +
$"<span {DR_Conception.TextBox1}></span></td><td><span {DR_Conception.Controls35}>Heure: </span></td><td>" +
$"<span {DR_Conception.TextBox2}></span></td></tr><tr><td><span {DR_Conception.Controls4}>Client: </span></td>" +
$"<td colspan=\"6\"><span {DR_Conception.Controls39} style=\"display:inline-block;width:100%;\">" +
$"</span></td></tr><tr><td><span {DR_Conception.Controls5}>Contact</span></td><td colspan=\"4\">" +
$"<span {DR_Conception.Controls40} style=\"display:inline-block;width:100%;\"></span></td><td>" +
$"<span {DR_Conception.Controls38}>Date de fermeture: </span></td><td>    <span {DR_Conception.TextBox3}>" +
$"</span></td></tr><tr><td><span {DR_Conception.Controls6}>Projet: </span></td><td colspan=\"2\">" +
$"<span {DR_Conception.Controls47} style=\"display:inline-block;width:100%;\"></span></td><td>" +
$"<span {DR_Conception.Controls36}>Tel: </span></td><td><span {DR_Conception.Controls41}></span></td><td>" +
$"<span {DR_Conception.Controls37}>Fax: </span></td><td><span {DR_Conception.Controls42}></span></td>" +
$"</tr></table><br /><table><tr align=\"center\"><td class=\"NoLignes\">#</td><td><span {DR_Conception.Controls30} " +
$"style=\"display:inline-block;width:100px;\">Date</span></td><td><span {DR_Conception.Controls31}" +
$" style=\"display:inline-block;width:300px;\">Contact</span></td><td><span {DR_Conception.Controls32} " +
$"style=\"display:inline-block;width:550px;\">Commentaires</span></td></tr><tr align=\"center\"><td class=\"NoLignes\">" +
$"<span {DR_Conception.Controls8}>1</span></td><td></td><td></td><td></td></tr><tr align=\"center\">" +
$"<td class=\"NoLignes\"><span {DR_Conception.Controls9}>2</span></td><td></td><td></td><td></td></tr>" +
$"<tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls10}>3</span></td><td></td><td></td><td></td>" +
$"</tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls11}>4</span></td><td></td><td></td><td></td>" +
$"</tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls12}>5</span></td><td></td><td></td><td></td>" +
$"</tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls13}>" +
$"6</span></td><td></td><td></td><td></td></tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls14}>" +
$"7</span></td><td></td><td></td><td></td></tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls15}>" +
$"8</span></td><td></td><td></td><td></td></tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls16}>" +
$"9</span></td><td></td><td></td><td></td></tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls17}>" +
$"10</span></td><td></td><td></td><td></td></tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls18}>" +
$"11</span></td><td></td><td></td><td></td></tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls19}>" +
$"12</span></td><td></td><td></td><td></td></tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls20}>" +
$"13</span></td><td></td><td></td><td></td></tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls21}>" +
$"14</span></td><td></td><td></td><td></td></tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls22}>" +
$"15</span></td><td></td><td></td><td></td></tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls23}>" +
$"16</span></td><td></td><td></td><td></td></tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls24}>" +
$"17</span></td><td></td><td></td><td></td></tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls25}>" +
$"18</span></td><td></td><td></td><td></td></tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls26}>" +
$"19</span></td><td></td><td></td><td></td></tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls27}>" +
$"20</span></td><td></td><td></td><td></td></tr><tr align=\"center\"><td class=\"NoLignes\"><span {DR_Conception.Controls28}>" +
$"21</span></td><td></td><td></td><td></td></tr></table></div></div></form></body></html>");
}
}
public class DR_DemandePrix
{
public static string lblTitreDemande;
/// Contrôle lblTitreFournisseur.

public static string lblTitreFournisseur;
/// Contrôle lblFournisseur.

public static string lblFournisseur;
/// Contrôle lblTitreNoSoum.

public static string lblTitreNoSoum;
/// Contrôle lblNoSoum.

public static string lblNoSoum;
/// Contrôle lblTitreNoGRB.

public static string lblTitreNoGRB;
/// Contrôle lblNoGRB.

public static string lblNoGRB;
/// Contrôle lblTitreContact.

public static string lblTitreContact;
/// Contrôle lblContact.

public static string lblContact;
/// Contrôle lblTitreTel.

public static string lblTitreTel;
/// Contrôle lblTel.

public static string lblTel;
/// Contrôle lblTitreDate.

public static string lblTitreDate;
/// Contrôle lblDate.

public static string lblDate;
/// Contrôle lblTitreDateReq.

public static string lblTitreDateReq;
/// Contrôle lblDateRequise.

public static string lblDateRequise;
/// Contrôle lblTitreFax.

public static string lblTitreFax;
/// Contrôle lblFax.

public static string lblFax;
/// Contrôle lblTitreComPar.

public static string lblTitreComPar;
/// Contrôle lblCommandePar.

public static string lblCommandePar;
/// Contrôle lblTitreTransport.

public static string lblTitreTransport;
/// Contrôle lblTransport.

public static string lblTransport;
/// Contrôle lblTitrePage.

public static string lblTitrePage;
/// Contrôle lblPage.

public static string lblPage;
/// Contrôle lblTitreQte.

public static string lblTitreQte;
/// Contrôle lblTitrePiece.

public static string lblTitrePiece;
/// Contrôle lblTitreDescription.

public static string lblTitreDescription;
/// Contrôle lblTitreManufact.

public static string lblTitreManufact;
/// Contrôle lblTitrePrix.

public static string lblTitrePrix;
/// Contrôle lblTitreDelais.

public static string lblTitreDelais;
/// Contrôle Label2.

public static string Label2;
/// Contrôle Label3.

public static string Label3;
/// Contrôle Label4.

public static string Label4;
/// Contrôle Label5.

public static string Label5;
/// Contrôle GridView1.

///GridView GridView1;
/// Contrôle Label6.

public static string Label6;
/// Contrôle lblTitreCommentaire.

public static string lblTitreCommentaire;
/// Contrôle lblCommentaire.

public static string lblCommentaire;
/// Contrôle lblPrixValide.

public static string lblPrixValide;
/// Contrôle TextBox1.

public static string TextBox1;
/// Contrôle lblJours.

public static string lblJours;
/// Contrôle lblAdresse.

public static string lblAdresse;
/// Contrôle lblPiedPage.

public static string lblPiedPage;

public static bool Orientation;
}
public class DR_FabricationFermeture
{
public static string lblGrandTotal; //lblGrandTotal
public static string Label3; //Fabrication - Fermeture
public static string Label7; //Soumission
public static string Label44; //Projet #
public static string lblSoum;
public static string lblProj;
public static string lblDate;
public static string lblProjetNom;
public static string lblDateOuverture;

public static string Label35; //Heure: 
public static string TextBox3;
public static string lblNom; //Client
public static string lblClient;

public static string Label5; //Contact
public static string lblContact;
public static string Label38; //Date de fermeture
public static string lblDatePrint;
public static string Label6; //Projet
public static string lblProjet;
public static string Label36; //Tel.: 
public static string lblTel;
public static string Label37; //Fax: 
public static string lblFax;
public static string lblGrandTotalKM; //lblGrandTotalKM
public static string Label8; //Documents obligatoires pour la fermeture du dossier
public static string Label16; //Liste de materiel
public static string Label9; //Dessin tel que construit
public static string Label47; //Rapport CSA
public static string Label48; //etiquette CSA
public static string Label49; //Fiche technique
public static string Label10; //Documents pour fin des fabrication
public static string Label15; //Description
public static string Label13; //Date
public static string Label14; //Nbre de page
public static string Label12; //Liste de materiel ATELIER
public static string TextBox1;
public static string TextBox4;
public static string Label17; //Dessins Mecaniques
public static string Label18; //# 
public static string Label31; //Dessins 
public static string Label27; //Revision
}
public class DR_Facturation
{
public static string lblTitreNumero;
public static string lblNumero;
public static string lblClient;
public static string lblDate;
public static string lblHeuresFacturees;
public static dynamic lblHeuresNonFacturees;
public static dynamic lblGrandTotal;
public static string lblDateDebut;
public static string lblDateFin;
public static string Label8;
public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public class DR_FacturationManuelle
{
/// Contrôle EnTeteAdresse.
public static string EnTeteAdresse;
/// Contrôle EnTeteTelFax.
public static string EnTeteTelFax;
/// Contrôle Label1.
public static string Label1;
/// Contrôle lblTitreNumero.
public static string lblTitreNumero;
/// Contrôle lblNumero.
public static string lblNumero;
/// Contrôle Label3.
public static string Label3;
/// Contrôle lblClient.
public static string lblClient;
/// Contrôle Label15.
public static string Label15;
/// Contrôle lblDateDebut.
public static string lblDateDebut;
/// Contrôle Label17.
public static string Label17;
/// Contrôle lblDateFin.
public static string lblDateFin;
public static string lblDate;
/// Contrôle Label8.
public static string Label8;
/// Contrôle Label13.
public static string Label13;
/// Contrôle lblHeuresFacturees.
public static string lblHeuresFacturees;
/// Contrôle Label11.
public static string Label11;
/// Contrôle lblHeuresNonFacturees.
public static string lblHeuresNonFacturees;
/// Contrôle Label10.
public static string Label10;
/// Contrôle lblGrandTotal.
public static string lblGrandTotal;
}
public class DR_FaxAnglais
{
public static string Label3;
/// Contrôle Label9.
public static string Label9;
/// Contrôle Label10.
public static string Label10;
/// Contrôle lblDate.
public static string lblDate;
/// Contrôle lblNoProjetSoum.
public static string lblNoProjetSoum;
/// Contrôle lblProjet.
public static string lblProjet;
/// Contrôle Label11.
public static string Label11;
/// Contrôle lblAttention.
public static string lblAttention;
/// Contrôle Label12.
public static string Label12;
/// Contrôle lblEntreprise.
public static string lblEntreprise;
/// Contrôle Label13.
public static string Label13;
/// Contrôle lblFax.
public static string lblFax;
/// Contrôle Label21.
public static string Label21;
/// Contrôle lblSujet.
public static string lblSujet;
/// Contrôle Label5.
public static string Label5;
/// Contrôle Label1.
public static string Label1;
/// Contrôle lblPage.
public static string lblPage;
/// Contrôle Label7.
public static string Label7;
/// Contrôle lblDe.
public static string lblDe;
/// Contrôle Label6.
public static string Label6;
/// Contrôle lblMessage.
public static string lblMessage;
/// Contrôle Label4.
public static string Label4;
/// Contrôle Label2.
public static string Label2;
/// Contrôle Label8.
public static string Label8;
public static bool Orientation = !WebGRB2024.Program.isLandscape;

}
public class DR_FaxFrancais
{
/// Contrôle Label9.
public static string Label9;
/// Contrôle Label14.
public static string Label14;
/// Contrôle Label10.
public static string Label10;
/// Contrôle lblDate.
public static string lblDate;
/// Contrôle lblNoProjetSoum.
public static string lblNoProjetSoum;
/// Contrôle lblProjet.
public static string lblProjet;
/// Contrôle Label11.
public static string Label11;
/// Contrôle lblAttention.
public static string lblAttention;
/// Contrôle Label12.
public static string Label12;
/// Contrôle lblEntreprise.
public static string lblEntreprise;
/// Contrôle Label13.
public static string Label13;
/// Contrôle lblFax.
public static string lblFax;
/// Contrôle Label21.
public static string Label21;
/// Contrôle lblSujet.
public static string lblSujet;
/// Contrôle Label5.
public static string Label5;
/// Contrôle Label1.
public static string Label1;
/// Contrôle lblPage.
public static string lblPage;
/// Contrôle Label7.
public static string Label7;
/// Contrôle lblDe.
public static string lblDe;
/// Contrôle Label6.
public static string Label6;
/// Contrôle lblMessage.
public static string lblMessage;
/// Contrôle Label4.
public static string Label4;
/// Contrôle Label2.
public static string Label2;
/// Contrôle Label8.
public static string Label8;
/// Contrôle Label3.
public static string Label3;
public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public class DR_FermeMeca
{
///EnTeteLogo.
///Image EnTeteLogo;
///EnTeteAdresse.
public static string EnTeteAdresse;
///EnTeteTelFax.
public static string EnTeteTelFax;
///Label3.
public static string Label3;
///Label7.
public static string Label7;
///Label44.
public static string Label44;
///LblSoum.
public static string LblSoum;
///LblProj.
public static string LblProj;
///Label1.
public static string Label1;
///LblDate.
public static string LblDate;
///Label2.
public static string Label2;
///LblProjetNom.
public static string LblProjetNom;
///Label33.
public static string Label33;
///LblDateOuverture.
public static string LblDateOuverture;
///Label34.
public static string Label34;
///TextBox2.
public static string TextBox2;
///Label35.
public static string Label35;
///TextBox3.
public static string TextBox3;
///Label4.
public static string Label4;
///LblClient.
public static string LblClient;
///Label5.
public static string Label5;
///LblContact.
public static string LblContact;
///Label38.
public static string Label38;
///TextBox5.
public static string TextBox5;
///Label6.
public static string Label6;
///LblProjet.
public static string LblProjet;
///Label36.
public static string Label36;
///LblTel.
public static string LblTel;
///Label37.
public static string Label37;
///LblFax.
public static string LblFax;
///Label8.
public static string Label8;
///Label16.
public static string Label16;
///Label9.
public static string Label9;
///Label11.
public static string Label11;
///Label10.
public static string Label10;
///Label15.
public static string Label15;
///Label13.
public static string Label13;
///Label14.
public static string Label14;
///Label12.
public static string Label12;
///TextBox1.
public static string TextBox1;
///TextBox4.
public static string TextBox4;
///Label17.
public static string Label17;
///Label18.
public static string Label18;
///Label30.
public static string Label30;
///Label31.
public static string Label31;
///Label32.
public static string Label32;
///Label27.
public static string Label27;
///Label28.
public static string Label28;
///Label19.
public static string Label19;
///Label20.
public static string Label20;
///Label21.
public static string Label21;
///Label22.
public static string Label22;
///Label23.
public static string Label23;
///Label24.
public static string Label24;
///Label25.
public static string Label25;
///Label26.
public static string Label26;
///Label29.
public static string Label29;
///Label39.
public static string Label39;
///Label40.
public static string Label40;
///Label41.
public static string Label41;
///Label42.
public static string Label42;
///Label43.
public static string Label43;
///Label45.
public static string Label45;
///Label46.
public static string Label46;
public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public class DR_Fermeture
{
///EnTeteLogo.
///Image EnTeteLogo;
///EnTeteAdresse.
public static string EnTeteAdresse;
///EnTeteTelFax.
public static string EnTeteTelFax;
///DR_FermetureLabel1.
public static string DR_FermetureLabel1;
///DR_FermetureLabel2.
public static string DR_FermetureLabel2;
///DR_FermetureLblDate.
public static string DR_FermetureLblDate;
///DR_FermetureLblNom.
public static string DR_FermetureLblNom;
///DR_FermetureLabel3.
public static string DR_FermetureLabel3;
///DR_FermetureLabel4.
public static string DR_FermetureLabel4;
///DR_FermetureLabel11.
public static string DR_FermetureLabel11;
///DR_FermetureLabel5.
public static string DR_FermetureLabel5;
///DR_FermetureLabel6.
public static string DR_FermetureLabel6;
///DR_FermetureLabel7.
public static string DR_FermetureLabel7;
///DR_FermetureLabel9.
public static string DR_FermetureLabel9;
///DR_FermetureLabel12.
public static string DR_FermetureLabel12;
///txtNomJour.
public static string txtNomJour;
///txtProjet.
public static string txtProjet;
///Text1.
public static string Text1;
///txtDescription.
public static string txtDescription;
///txtJournee.
public static string txtJournee;
///txtA.
public static string txtA;
///txtTotal.
public static string txtTotal;
///Text2.
public static string Text2;

public static bool Orientation = !WebGRB2024.Program.isLandscape;

public static string Controls117;
public static string Controls118;
public static string Controls119;
public static string Controls120;
public static string Controls121;
public static string Controls122;
public static string Controls123;
public static string Controls124;
public static string Controls125;
public static string Controls126;
}
public class DR_FeuilleTemps
{
public static string Label2;
/// Contrôle lblSemaine.
public static string lblSemaine;
/// Contrôle lblUtilisateur.
public static string lblUtilisateur;
/// Contrôle lblTotalKM.
public static string lblTotalKM;
/// Contrôle lblTotalHeures.
public static string lblTotalHeures;
public static string lblGrandTotalKM;
public static double lblGrandTotal;
public static string lblDatePrint;
public static string lblDate;
public static string lblNom;

public static bool Orientation = !WebGRB2024.Program.isLandscape;
public static Recordset DataSource;
}
public class DR_FinFab
{
/// Contrôle form1.

/// Contrôle Impression.
///Panel Impression;
/// Contrôle EnTeteLogo.
///Image EnTeteLogo;
/// Contrôle Label3.
public static string Label3;
/// Contrôle Label53.
public static string Label53;
/// Contrôle TextBox1.
public static string TextBox1;
/// Contrôle Label59.
public static string Label59;
/// Contrôle TextBox2.
public static string TextBox2;
/// Contrôle Label1.
public static string Label1;
/// Contrôle TextBox3.
public static string TextBox3;
/// Contrôle Label17.
public static string Label17;
/// Contrôle Label18.
public static string Label18;
/// Contrôle Label30.
public static string Label30;
/// Contrôle Label31.
public static string Label31;
/// Contrôle Label32.
public static string Label32;
/// Contrôle Label27.
public static string Label27;
/// Contrôle Label28.
public static string Label28;
/// Contrôle Label19.
public static string Label19;
/// Contrôle Label20.
public static string Label20;
/// Contrôle Label21.
public static string Label21;
/// Contrôle Label22.
public static string Label22;
/// Contrôle Label23.
public static string Label23;
/// Contrôle Label24.
public static string Label24;
/// Contrôle Label25.
public static string Label25;
/// Contrôle Label26.
public static string Label26;
/// Contrôle Label29.
public static string Label29;
/// Contrôle Label39.
public static string Label39;
/// Contrôle Label40.
public static string Label40;
/// Contrôle Label41.
public static string Label41;
/// Contrôle Label42.
public static string Label42;
/// Contrôle Label43.
public static string Label43;
/// Contrôle Label45.
public static string Label45;
/// Contrôle Label46.
public static string Label46;
/// Contrôle Label2.
public static string Label2;
/// Contrôle Label4.
public static string Label4;
/// Contrôle Label5.
public static string Label5;
/// Contrôle Label6.
public static string Label6;
/// Contrôle Label7.
public static string Label7;
/// Contrôle Label8.
public static string Label8;

public static bool Orientation;
}
public class DR_Fournisseur
{
///EnTeteLogo.
///Image EnTeteLogo;
///EnTeteAdresse.
public static string EnTeteAdresse;
///EnTeteTelFax.
public static string EnTeteTelFax;
///DR_FounisseurLabel3.
public static string DR_FounisseurLabel3;
///DR_FounisseurLabel7.
public static string DR_FounisseurLabel7;
///DR_FounisseurLabel29.
public static string DR_FounisseurLabel29;
///TextBox1.
public static string TextBox1;
///TextBox2.
public static string TextBox2;
///DR_FounisseurLabel1.
public static string DR_FounisseurLabel1;
///DR_FounisseurLblDate.
public static string DR_FounisseurLblDate;
///DR_FounisseurLabel2.
public static string DR_FounisseurLabel2;
///TextBox3.
public static string TextBox3;
///DR_FounisseurLabel33.
public static string DR_FounisseurLabel33;
///DR_FounisseurLblDateOuverture.
public static string DR_FounisseurLblDateOuverture;
///DR_FounisseurLabel34.
public static string DR_FounisseurLabel34;
///DR_FounisseurLblDateDue.
public static string DR_FounisseurLblDateDue;
///DR_FounisseurLabel35.
public static string DR_FounisseurLabel35;
///TextBox4.
public static string TextBox4;
///DR_FounisseurLabel4.
public static string DR_FounisseurLabel4;
///DR_FounisseurLblClient.
public static string DR_FounisseurLblClient;
///DR_FounisseurLabel5.
public static string DR_FounisseurLabel5;
///DR_FounisseurLblContact.
public static string DR_FounisseurLblContact;
///DR_FounisseurLabel38.
public static string DR_FounisseurLabel38;
///TextBox5.
public static string TextBox5;
///DR_FounisseurLabel6.
public static string DR_FounisseurLabel6;
///DR_FounisseurLblProjet.
public static string DR_FounisseurLblProjet;
///DR_FounisseurLabel36.
public static string DR_FounisseurLabel36;
///DR_FounisseurLblTel.
public static string DR_FounisseurLblTel;
///DR_FounisseurLabel37.
public static string DR_FounisseurLabel37;
///DR_FounisseurLblFax.
public static string DR_FounisseurLblFax;
///DR_FounisseurLabel30.
public static string DR_FounisseurLabel30;
///DR_FounisseurLabel31.
public static string DR_FounisseurLabel31;
///DR_FounisseurLabel32.
public static string DR_FounisseurLabel32;
///DR_FounisseurLabel8.
public static string DR_FounisseurLabel8;
///TextBox6.
public static string TextBox6;
///TextBox7.
public static string TextBox7;
///TextBox8.
public static string TextBox8;
///DR_FounisseurLabel9.
public static string DR_FounisseurLabel9;
///TextBox9.
public static string TextBox9;
///TextBox10.
public static string TextBox10;
///TextBox11.
public static string TextBox11;
///DR_FounisseurLabel10.
public static string DR_FounisseurLabel10;
///TextBox12.
public static string TextBox12;
///TextBox13.
public static string TextBox13;
///TextBox14.
public static string TextBox14;
///DR_FounisseurLabel11.
public static string DR_FounisseurLabel11;
///TextBox15.
public static string TextBox15;
///TextBox16.
public static string TextBox16;
///TextBox17.
public static string TextBox17;
///DR_FounisseurLabel12.
public static string DR_FounisseurLabel12;
///TextBox18.
public static string TextBox18;
///TextBox19.
public static string TextBox19;
///TextBox20.
public static string TextBox20;
///DR_FounisseurLabel13.
public static string DR_FounisseurLabel13;
///TextBox21.
public static string TextBox21;
///TextBox22.
public static string TextBox22;
///TextBox23.
public static string TextBox23;
///DR_FounisseurLabel14.
public static string DR_FounisseurLabel14;
///TextBox24.
public static string TextBox24;
///TextBox25.
public static string TextBox25;
///TextBox26.
public static string TextBox26;
///DR_FounisseurLabel15.
public static string DR_FounisseurLabel15;
///TextBox27.
public static string TextBox27;
///TextBox28.
public static string TextBox28;
///TextBox29.
public static string TextBox29;
///DR_FounisseurLabel16.
public static string DR_FounisseurLabel16;
///TextBox30.
public static string TextBox30;
///TextBox31.
public static string TextBox31;
///TextBox32.
public static string TextBox32;
///DR_FounisseurLabel17.
public static string DR_FounisseurLabel17;
///TextBox33.
public static string TextBox33;
///TextBox34.
public static string TextBox34;
///TextBox35.
public static string TextBox35;
///DR_FounisseurLabel18.
public static string DR_FounisseurLabel18;
///TextBox36.
public static string TextBox36;
///TextBox37.
public static string TextBox37;
///TextBox38.
public static string TextBox38;
///DR_FounisseurLabel19.
public static string DR_FounisseurLabel19;
///TextBox39.
public static string TextBox39;
///TextBox40.
public static string TextBox40;
///TextBox41.
public static string TextBox41;
///DR_FounisseurLabel20.
public static string DR_FounisseurLabel20;
///TextBox42.
public static string TextBox42;
///TextBox43.
public static string TextBox43;
///TextBox44.
public static string TextBox44;
///DR_FounisseurLabel21.
public static string DR_FounisseurLabel21;
///TextBox45.
public static string TextBox45;
///TextBox46.
public static string TextBox46;
///TextBox47.
public static string TextBox47;
///DR_FounisseurLabel22.
public static string DR_FounisseurLabel22;
///TextBox48.
public static string TextBox48;
///TextBox49.
public static string TextBox49;
///TextBox50.
public static string TextBox50;
public static string lblClient;
public static string lblContact;
public static string lblTel;
public static string lblFax;
public static string lblNoSoum;
public static string lblNoProj;
public static string lblProjetNom;
public static string lblDate;
public static string lblDateOuverture;
public static string lblDateDue;
public static string lblProjet;

public static bool Orientation;
}
public class DR_Inventaire
{
public static string lblDate;
public static dynamic lblTotal;
public static string lblTitre;
public static Recordset DataSource;
public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public class DR_InventaireM
{
///lvwInventaireAjust.
///GridView lvwInventaireAjust;
}
public class DR_Liste_piece
{
public DR_Liste_piece()
{
}
public static Recordset DataSource;
public static string lblDate;
public static string lblProjet;
public static string lblSoumission;
public static string lblDescription;
public static string lblClient;
public static string lblContact;
public static bool rptOrientPortrait;
public static bool Orientation;
public static bool lblTitreNoFactureVisible;
public static bool lblNoFactureVisible;
public static string lblNoFacture;
public static string lbldate;
public static string lblTitreProjet;
public static string lblTitreSoumission;
public static string lblTitreQuantite;
public static string lblTitreNoItem;
public static string lblTitreManufacturier;
public static string lblTitreID;
public static string lblNoPage;
public static string lblsoumission;
public static string Label1 = "149, rue Pierre Paradis, St-Alphonse-de-Granby, QC J0E 2A4";
public static string Label2 = "Tel: (450) 372-0021  Fax: (450) 372-3860";
public static string lblTitreClient; //"Client: 
public static string lblTitreContact; //"Contact: 
public static string lblcontact;
public static string Label4; //"Description: 
public static string lbldescription;
public static string lblTitreNoFacture; //"Facture: 
public static string TextBox2;
public static string lblTitreDescription; //"Description"
public static string lblTitreid; //"# id"
public static string Label3; //"CSA Verifie"
public static string Text1; //"Qte"
public static string Text6; //"No. Item"
public static string Text3; //"Description"
public static string Text4; //"Manufacturier"
public static string Text5; //"# id"
}
public class DR_ListeAchats
{
public static string EnTeteAdresse;
public static string EnTeteTelFax;
public static string Label2;
///lblNumero.
public static string lblNumero;
///Label14.
public static string Label14;
///lblDate.
public static string lblDate;
///Label3.
public static string Label3;
///Label4.
public static string Label4;
///Label6.
public static string Label6;
///Label5.
public static string Label5;
///Label8.
public static string Label8;
///Label7.
public static string Label7;
///Label9.
public static string Label9;
///Label10.
public static string Label10;
///Label16.
public static string Label16;
///Label11.
public static string Label11;
///Label12.
public static string Label12;
///Label13.
public static string Label13;
///Label17.
public static string Label17;
///GridView1.
///GridView GridView1;
///lblDateImpression.
public static string lblDateImpression;
///TextBox1.
public static string TextBox1;
///Label18.
public static string Label18;
///Label33.
public static string Label33;
///Label19.
public static string Label19;
///lblTotal.
public static string lblTotal;

public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public class DR_ListeClient
{
///Impression.
///Panel Impression;
///EnTeteLogo.
///Image EnTeteLogo;
///EnTeteAdresse.
public static string EnTeteAdresse;
///EnTeteTelFax.
public static string EnTeteTelFax;
///Label2.
public static string Label2;
///Label4.
public static string Label4;
///Label9.
public static string Label9;
///Label10.
public static string Label10;
///Label3.
public static string Label3;
///Label7.
public static string Label7;
///Label5.
public static string Label5;
///Text1.
public static string Text1;
///Text3.
public static string Text3;
///Text6.
public static string Text6;
///Text9.
public static string Text9;
///Text12.
public static string Text12;
///Text11.
public static string Text11;
///Text10.
public static string Text10;
///Text4.
public static string Text4;
///Text2.
public static string Text2;
///Text5.
public static string Text5;
///GridView1.
///GridView GridView1;
///Label1.
public static string Label1;
///TextBox2.
public static string TextBox2;
///Label6.
public static string Label6;
///TextBox3.
public static string TextBox3;
public static bool Orientation = !WebGRB2024.Program.isLandscape;
public static Recordset DataSource;
}
public class DR_ListeContact
{
/// Contrôle Label2.
public static string Label2;
/// Contrôle Filler.
public static string Filler;
/// Contrôle Mode.
///Panel Mode;
/// Contrôle Text1.
public static string Text1;
/// Contrôle Text2.
public static string Text2;
/// Contrôle Text3.
public static string Text3;
/// Contrôle Text9.
public static string Text9;
/// Contrôle Text7.
public static string Text7;
/// Contrôle Text4.
public static string Text4;
/// Contrôle Text5.
public static string Text5;
/// Contrôle Text6.
public static string Text6;
public static string lblDateImpression;
public static bool Orientation = !WebGRB2024.Program.isLandscape;

public static Recordset DataSource;
}
public class DR_ListeFournisseur
{
public static Recordset DataSource;
public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public class DR_ListeInventaire
{
///Impression.
///Panel Impression;
///EnTeteLogo.
///Image EnTeteLogo;
///EnTeteAdresse.
public static string EnTeteAdresse;
///EnTeteTelFax.
public static string EnTeteTelFax;
///lblTitre.
public static string lblTitre;
///Label2.
public static string Label2;
///Label3.
public static string Label3;
///Label4.
public static string Label4;
///Label5.
public static string Label5;
///Label1.
public static string Label1;
///Label6.
public static string Label6;
///txtNoItem.
public static string txtNoItem;
///txtDescription.
public static string txtDescription;
///txtManufacturier.
public static string txtManufacturier;
///txtLocalisation.
public static string txtLocalisation;
///Text1.
public static string Text1;
///Shape2.
public static string Shape2;
///GridView1.
///GridView GridView1;
///lblDateImpression.
public static string lblDateImpression;
///Label18.
public static string Label18;
public static string lblDate;

public static Recordset DataSource { get;set; }
public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public partial class DR_ListeProjet
{
public static string EnTeteAdresse;
//EnTeteTelFax//
public static string EnTeteTelFax;
//lblTitre//
public static string lblTitre;
//Label15//
public static string Label15;
//TextBox1//
public static string TextBox1;
//Label17//
public static string Label17;
//TextBox2//
public static string TextBox2;
//Label1//
public static string Label1;
//Label2//
public static string Label2;
//Text4//
public static string Text4;
//Text5//
public static string Text5;
//GridView1//

//lblDateImpression//
public static string lblDateImpression;
//Label18//
public static string Label18;
public static string lblDateDebut;
public static string lblDateFin;
public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public partial class DR_OutilsInOut
{
public static string EnTeteAdresse;
//EnTeteTelFax//
public static string EnTeteTelFax;
//lblTitre//
public static string lblTitre;
//Label1//
public static string Label1;
//Label6//
public static string Label6;
//Label4//
public static string Label4;
//Label5//
public static string Label5;
//Label2//
public static string Label2;
//Label3//
public static string Label3;
//txtno//
public static string txtno;
//txtnom//
public static string txtnom;
//txttype//
public static string txttype;
//txtcout//
public static string txtcout;
//txtachat//
public static string txtachat;
//txthorsfonction//
public static string txthorsfonction;
//GridView1//

//lblDateImpression//
public static string lblDateImpression;
//Label18//
public static string Label18;
public static string lbldepartement;
public static string lbldate;
public static Recordset DataSource
{
get;
set;
}
public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public partial class DR_OutilsMachinerie
{
public static string EnTeteAdresse;
public static string EnTeteTelFax;
public static string lblTitre;
public static string Label1;
public static string Label6;
public static string Label4;
public static string Label5;
public static string Label2;
public static string Label3;
public static string Label8;
public static string txtno;
public static string txtnom;
public static string txttype;
public static string txtcout;
public static string txtachat;
public static string txthorsfonction;
public static string txtcommentaire;
public static string lbldepartement;
public static string lbldate;
public static string lblDateImpression;
public static string Label18;
public static Recordset DataSource;
public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public partial class DR_Probleme
{
public static string DR_ProblemesLblTitreProjSoum;
public static string DR_ProblemesLblNoProjSoum;
public static string DR_ProblemesLabel2;
public static string DR_ProblemesLblNomEmploye;
public static string DR_ProblemesLabel3;
public static string DR_ProblemesLabel5;
public static string DR_ProblemesLabel1;
public static string DR_ProblemesLabel4;
public static string DR_ProblemesLabel6;
public static string DR_ProblemesLabel7;
public static string DR_ProblemesLabel8;
public static string DR_ProblemesLabel9;
public static string DR_ProblemesLabel10;
public static string DR_ProblemesLabel11;
public static string DR_ProblemesLabel12;
public static string DR_ProblemesLabel13;
public static string DR_ProblemesLabel14;
public static string lblTitreProjSoum; //Projet #
public static string lblNoProjSoum;
public static string Label2; //Nom de l'employe
public static string lblNomEmploye;
public static string TextBox1;
public static string TextBox2;
public static string TextBox3;
public static string TextBox4;
public static string TextBox5;
public static string Label3; //#
public static string Label5; //Problèmes rencontres
public static string Label1; //Date"
public static string Label4; //1
public static string TextBox6;
public static string TextBox7;
public static string Label6; //2
public static string TextBox8;
public static string TextBox9;
public static string Label7; //3
public static string TextBox10;
public static string TextBox11;
public static string Label8; //4
public static string TextBox12;
public static string TextBox13;
public static string Label9; //5
public static string TextBox14;
public static string TextBox15;
public static string Label10; //6
public static string TextBox16;
public static string TextBox17;
public static string Label11; //7
public static string TextBox18;
public static string TextBox19;
public static string Label12; //8
public static string TextBox20;
public static string TextBox21;
public static string Label13; //9
public static string TextBox22;
public static string TextBox23;
public static string Label14; //10
public static string TextBox24;
public static string TextBox25;
public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public class DR_Programmation
{

// Contrôle Label3//
public static string Label3;

public static string Label7;
// Contrôle Label22//
public static string Label22;
// Contrôle TextBox1//
public static string TextBox1;
// Contrôle TextBox2//
public static string TextBox2;
// Contrôle Label1//
public static string Label1;
// Contrôle lblDate//
public static string lblDate;
// Contrôle Label2//
public static string Label2;
// Contrôle lblProjetNom//
public static string lblProjetNom;
// Contrôle Label33//
public static string Label33;
// Contrôle lblMDPAutomate//
public static string lblMDPAutomate;
// Contrôle Label34//
public static string Label34;
// Contrôle lblMDPAutre//
public static string lblMDPAutre;
// Contrôle Label4//
public static string Label4;
// Contrôle lblClient//
public static string lblClient;
// Contrôle Label5//
public static string Label5;
// Contrôle lblContact//
public static string lblContact;
// Contrôle Label38//
public static string Label38;
// Contrôle TextBox5//
public static string TextBox5;
// Contrôle Label6//
public static string Label6;
// Contrôle lblProjetClient//
public static string lblProjetClient;
// Contrôle Label36//
public static string Label36;
// Contrôle lblTelephone//
public static string lblTelephone;
// Contrôle Label37//
public static string Label37;
// Contrôle lblFax//
public static string lblFax;
// Contrôle Label8//
public static string Label8;
// Contrôle Label13//
public static string Label13;
// Contrôle Label9//
public static string Label9;
// Contrôle Label14//
public static string Label14;
// Contrôle Label10//
public static string Label10;
// Contrôle Label15//
public static string Label15;
// Contrôle Label11//
public static string Label11;
// Contrôle Label16//
public static string Label16;
// Contrôle Label12//
public static string Label12;
// Contrôle Label17//
public static string Label17;
// Contrôle TextBox3//
public static string TextBox3;
// Contrôle Label18//
public static string Label18;
// Contrôle TextBox4//
public static string TextBox4;
// Contrôle Label21//
public static string Label21;
// Contrôle Label19//
public static string Label19;
// Contrôle Label20//
public static string Label20;
// Contrôle Label23//
public static string Label23;
// Contrôle TextBox6//
public static string TextBox6;
// Contrôle TextBox8//
public static string TextBox8;
// Contrôle TextBox9//
public static string TextBox9;
// Contrôle TextBox7//
public static string TextBox7;
// Contrôle TextBox10//
public static string TextBox10;
// Contrôle TextBox11//
public static string TextBox11;
// Contrôle TextBox12//
public static string TextBox12;
// Contrôle TextBox13//
public static string TextBox13;
// Contrôle TextBox14//
public static string TextBox14;
// Contrôle TextBox15//
public static string TextBox15;
// Contrôle TextBox16//
public static string TextBox16;
// Contrôle TextBox17//
public static string TextBox17;
// Contrôle TextBox18//
public static string TextBox18;
// Contrôle TextBox19//
public static string TextBox19;
// Contrôle TextBox20//
public static string TextBox20;
// Contrôle TextBox21//
public static string TextBox21;
// Contrôle TextBox22//
public static string TextBox22;
// Contrôle TextBox23//
public static string TextBox23;
// Contrôle TextBox24//
public static string TextBox24;
// Contrôle TextBox25//
public static string TextBox25;
// Contrôle TextBox26//
public static string TextBox26;
// Contrôle TextBox27//
public static string TextBox27;
// Contrôle TextBox28//
public static string TextBox28;
// Contrôle TextBox29//
public static string TextBox29;
// Contrôle TextBox30//
public static string TextBox30;
// Contrôle TextBox31//
public static string TextBox31;
// Contrôle TextBox32//
public static string TextBox32;
// Contrôle TextBox33//
public static string TextBox33;
// Contrôle TextBox34//
public static string TextBox34;
// Contrôle TextBox35//
public static string TextBox35;
// Contrôle TextBox36//
public static string TextBox36;
// Contrôle TextBox37//
public static string TextBox37;
// Contrôle TextBox38//
public static string TextBox38;
// Contrôle TextBox39//
public static string TextBox39;
// Contrôle TextBox40//
public static string TextBox40;
// Contrôle TextBox41//
public static string TextBox41;
// Contrôle TextBox42//
public static string TextBox42;
// Contrôle TextBox43//
public static string TextBox43;
// Contrôle TextBox44//
public static string TextBox44;
// Contrôle TextBox45//
public static string TextBox45;
// Contrôle TextBox46//
public static string TextBox46;
// Contrôle TextBox47//
public static string TextBox47;
// Contrôle TextBox48//
public static string TextBox48;
// Contrôle TextBox49//
public static string TextBox49;
// Contrôle TextBox50//
public static string TextBox50;
// Contrôle TextBox51//
public static string TextBox51;
// Contrôle TextBox52//
public static string TextBox52;
// Contrôle TextBox53//
public static string TextBox53;
// Contrôle TextBox54//
public static string TextBox54;
// Contrôle TextBox55//
public static string TextBox55;
// Contrôle TextBox56//
public static string TextBox56;
// Contrôle TextBox57//
public static string TextBox57;
// Contrôle TextBox58//
public static string TextBox58;
// Contrôle TextBox59//
public static string TextBox59;
// Contrôle TextBox60//
public static string TextBox60;
// Contrôle TextBox61//
public static string TextBox61;
// Contrôle TextBox62//
public static string TextBox62;
// Contrôle TextBox63//
public static string TextBox63;
// Contrôle TextBox64//
public static string TextBox64;
// Contrôle TextBox65//
public static string TextBox65;
// Contrôle TextBox66//
public static string TextBox66;
// Contrôle TextBox67//
public static string TextBox67;
// Contrôle TextBox68//
public static string TextBox68;
// Contrôle TextBox69//
public static string TextBox69;
// Contrôle TextBox70//
public static string TextBox70;
// Contrôle TextBox71//
public static string TextBox71;
// Contrôle TextBox72//
public static string TextBox72;
// Contrôle TextBox73//
public static string TextBox73;
// Contrôle TextBox74//
public static string TextBox74;
// Contrôle TextBox75//
public static string TextBox75;
// Contrôle TextBox76//
public static string TextBox76;
// Contrôle TextBox77//
public static string TextBox77;
// Contrôle TextBox78//
public static string TextBox78;
// Contrôle TextBox79//
public static string TextBox79;
// Contrôle TextBox80//
public static string TextBox80;
// Contrôle TextBox81//
public static string TextBox81;
// Contrôle TextBox82//
public static string TextBox82;
// Contrôle TextBox83//
public static string TextBox83;
// Contrôle TextBox84//
public static string TextBox84;
// Contrôle TextBox85//
public static string TextBox85;
// Contrôle TextBox86//
public static string TextBox86;
// Contrôle TextBox87//
public static string TextBox87;
// Contrôle TextBox88//
public static string TextBox88;
// Contrôle TextBox89//
public static string TextBox89;
// Contrôle ListView1//

public static string lblNoSoum;
public static string lblNoProj;
public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public class DR_ProjSoumElec
{
public static string lblFormTitle;
// Contrôle lblTotalTemps//
public static string lblTotalTemps;
// Contrôle txtTotalTemps//
public static string txtTotalTemps;
// Contrôle lblTotalPieces//
public static string lblTotalPieces;
// Contrôle txtTotalPieces//
public static string txtTotalPieces;
// Contrôle Label5//
public static string Label5;
// Contrôle txtProfit//
public static string txtProfit;
// Contrôle lblImprevus//
public static string lblImprevus;
// Contrôle txtImprevus//
public static string txtImprevus;
// Contrôle Label8//
public static string Label8;
// Contrôle txtCommission//
public static string txtCommission;
// Contrôle Label7//
public static string Label7;
// Contrôle txtPrixTotal//
public static string txtPrixTotal;
// Contrôle lblPasTemps//
public static string lblPasTemps;
// Contrôle txtChoix//
public static string txtChoix;
// Contrôle txtNoProjSoum//
public static string txtNoProjSoum;
// Contrôle lblNoSoumission//
public static string lblNoSoumission;
// Contrôle txtNoSoumission//
public static string txtNoSoumission;
// Contrôle Label26//
public static string Label26;
// Contrôle txtTransport//
public static string txtTransport;
// Contrôle Label2//
public static string Label2;
// Contrôle txtCheminPhotos//
public static string txtCheminPhotos;
// Contrôle Label4//
public static string Label4;
// Contrôle txtClient//
public static string txtClient;
// Contrôle lblPrixReception//
public static string lblPrixReception;
// Contrôle txtPrixReception//
public static string txtPrixReception;
// Contrôle Label3//
public static string Label3;
// Contrôle txtForfait//
public static string txtForfait;
// Contrôle lblForfaitInitiale//
public static string lblForfaitInitiale;
// Contrôle Label6//
public static string Label6;
// Contrôle txtContact//
public static string txtContact;
// Contrôle lblPrixSoumission//
public static string lblPrixSoumission;
// Contrôle txtPrixSoumission//
public static string txtPrixSoumission;
// Contrôle lblDateFacturation//
public static string lblDateFacturation;
// Contrôle txtDateFacturation//
public static string txtDateFacturation;
// Contrôle lblProjet//
public static string lblProjet;
// Contrôle txtProjet//
public static string txtProjet;
// Contrôle lblfraManuel//
public static string lblfraManuel;
// Contrôle Label23//
public static string Label23;
// Contrôle txtNbreManuel//
public static string txtNbreManuel;
// Contrôle Label22//
public static string Label22;
// Contrôle txtPrixManuel//
public static string txtPrixManuel;
// Contrôle Label21//
public static string Label21;
// Contrôle txtDelais//
public static string txtDelais;
// Contrôle lblSections//
public static string lblSections;
// Contrôle lblPiece//
public static string lblPiece;
// Contrôle lblTri//
public static string lblTri;
// Contrôle lblfraPieceTrouve//
public static string lblfraPieceTrouve;
// Contrôle lblfraPrixPiece//
public static string lblfraPrixPiece;
// Contrôle Label11//
public static string Label11;
// Contrôle Label12//
public static string Label12;
// Contrôle txtPrixList//
public static string txtPrixList;
// Contrôle Label13//
public static string Label13;
// Contrôle mskEscompte//
public static string mskEscompte;
// Contrôle Label14//
public static string Label14;
// Contrôle txtPrixNet//
public static string txtPrixNet;
// Contrôle Label15//
public static string Label15;
// Contrôle txtPrixSpecial//
public static string txtPrixSpecial;
// Contrôle lblfraDateRequise//
public static string lblfraDateRequise;
// Contrôle lblfraCommentaire//
public static string lblfraCommentaire;
// Contrôle txtCommentaire//
public static string txtCommentaire;
}
public class DR_ProjSoumMec
{
public static string lblFormTitle;
// Contrôle lblTotalTemps//
public static string lblTotalTemps;
// Contrôle txtTotalTemps//
public static string txtTotalTemps;
// Contrôle lblTotalPieces//
public static string lblTotalPieces;
// Contrôle txtTotalPieces//
public static string txtTotalPieces;
// Contrôle Label5//
public static string Label5;
// Contrôle txtProfit//
public static string txtProfit;
// Contrôle lblImprevus//
public static string lblImprevus;
// Contrôle txtImprevus//
public static string txtImprevus;
// Contrôle Label8//
public static string Label8;
// Contrôle txtCommission//
public static string txtCommission;
// Contrôle Label7//
public static string Label7;
// Contrôle txtPrixTotal//
public static string txtPrixTotal;
// Contrôle lblPasTemps//
public static string lblPasTemps;
// Contrôle txtChoix//
public static string txtChoix;
// Contrôle txtNoProjSoum//
public static string txtNoProjSoum;
// Contrôle lblNoSoumission//
public static string lblNoSoumission;
// Contrôle txtNoSoumission//
public static string txtNoSoumission;
// Contrôle Label26//
public static string Label26;
// Contrôle txtTransport//
public static string txtTransport;
// Contrôle Label2//
public static string Label2;
// Contrôle txtCheminPhotos//
public static string txtCheminPhotos;
// Contrôle Label4//
public static string Label4;
// Contrôle txtClient//
public static string txtClient;
// Contrôle lblPrixReception//
public static string lblPrixReception;
// Contrôle txtPrixReception//
public static string txtPrixReception;
// Contrôle Label3//
public static string Label3;
// Contrôle txtForfait//
public static string txtForfait;
// Contrôle lblForfaitInitiale//
public static string lblForfaitInitiale;
// Contrôle Label6//
public static string Label6;
// Contrôle txtContact//
public static string txtContact;
// Contrôle lblPrixSoumission//
public static string lblPrixSoumission;
// Contrôle txtPrixSoumission//
public static string txtPrixSoumission;
// Contrôle lblDateFacturation//
public static string lblDateFacturation;
// Contrôle txtDateFacturation//
public static string txtDateFacturation;
// Contrôle lblProjet//
public static string lblProjet;
// Contrôle txtProjet//
public static string txtProjet;
// Contrôle lblfraManuel//
public static string lblfraManuel;
// Contrôle Label23//
public static string Label23;
// Contrôle txtNbreManuel//
public static string txtNbreManuel;
// Contrôle Label22//
public static string Label22;
// Contrôle txtPrixManuel//
public static string txtPrixManuel;
// Contrôle Label21//
public static string Label21;
// Contrôle txtDelais//
public static string txtDelais;
// Contrôle lblSections//
public static string lblSections;
// Contrôle lblPiece//
public static string lblPiece;
// Contrôle lblTri//
public static string lblTri;
// Contrôle lblfraPieceTrouve//
public static string lblfraPieceTrouve;
// Contrôle lblfraPrixPiece//
public static string lblfraPrixPiece;
// Contrôle Label11//
public static string Label11;
// Contrôle Label12//
public static string Label12;
// Contrôle txtPrixList//
public static string txtPrixList;
// Contrôle Label13//
public static string Label13;
// Contrôle mskEscompte//
public static string mskEscompte;
// Contrôle Label14//
public static string Label14;
// Contrôle txtPrixNet//
public static string txtPrixNet;
// Contrôle Label15//
public static string Label15;
// Contrôle txtPrixSpecial//
public static string txtPrixSpecial;
// Contrôle lblfraDateRequise//
public static string lblfraDateRequise;
// Contrôle lblfraCommentaire//
public static string lblfraCommentaire;
// Contrôle txtCommentaire//
public static string txtCommentaire;
public static bool Orientation = !WebGRB2024.Program.isLandscape;

}
public class DR_ProjSoumMecTemps
{
public static string lblfraRessourcesHumaines;
public static string Label8;
public static string Label9;
public static string Label54;
public static string Label56;
public static string Label57;
public static string Label58;
public static string Label7;
public static string txtTempsDessinSoum;
public static string txtTempsDessinProj;
public static string txtTempsDessinConc;
public static string lblTempsDessinReel;
public static string Label16;
public static string lblPrixDessin;
public static string Label30;
public static string Label2;
public static string txtTempsCoupeSoum;
public static string txtTempsCoupeProj;
public static string txtTempsCoupeConc;
public static string lblTempsCoupeReel;
public static string Label15;
public static string lblPrixCoupe;
public static string Label18;
public static string Label1;
public static string txtTempsMachinageSoum;
public static string txtTempsMachinageProj;
public static string txtTempsMachinageConc;
// Contrôle lblTempsMachinageReel//
public static string lblTempsMachinageReel;
// Contrôle Label51//
public static string Label51;
// Contrôle lblPrixMachinage//
public static string lblPrixMachinage;
// Contrôle Label19//
public static string Label19;
// Contrôle Label3//
public static string Label3;
// Contrôle txtTempsSoudureSoum//
public static string txtTempsSoudureSoum;
// Contrôle txtTempsSoudureProj//
public static string txtTempsSoudureProj;
// Contrôle txtTempsSoudureConc//
public static string txtTempsSoudureConc;
// Contrôle lblTempsSoudureReel//
public static string lblTempsSoudureReel;
// Contrôle Label66//
public static string Label66;
// Contrôle lblPrixSoudure//
public static string lblPrixSoudure;
// Contrôle Label21//
public static string Label21;
// Contrôle Label5//
public static string Label5;
// Contrôle txtTempsAssemblageSoum//
public static string txtTempsAssemblageSoum;
// Contrôle txtTempsAssemblageProj//
public static string txtTempsAssemblageProj;
// Contrôle txtTempsAssemblageConc//
public static string txtTempsAssemblageConc;
// Contrôle lblTempsAssemblageReel//
public static string lblTempsAssemblageReel;
// Contrôle Label55//
public static string Label55;
// Contrôle lblPrixAssemblage//
public static string lblPrixAssemblage;
// Contrôle Label22//
public static string Label22;
// Contrôle Label4//
public static string Label4;
// Contrôle txtTempsPeintureSoum//
public static string txtTempsPeintureSoum;
// Contrôle txtTempsPeintureProj//
public static string txtTempsPeintureProj;
// Contrôle txtTempsPeintureConc//
public static string txtTempsPeintureConc;
// Contrôle lblTempsPeintureReel//
public static string lblTempsPeintureReel;
// Contrôle Label14//
public static string Label14;
// Contrôle lblPrixPeinture//
public static string lblPrixPeinture;
// Contrôle Label32//
public static string Label32;
// Contrôle Label6//
public static string Label6;
// Contrôle txtTempsTestSoum//
public static string txtTempsTestSoum;
// Contrôle txtTempsTestProj//
public static string txtTempsTestProj;
// Contrôle txtTempsTestConc//
public static string txtTempsTestConc;
// Contrôle lblTempsTestReel//
public static string lblTempsTestReel;
// Contrôle Label13//
public static string Label13;
// Contrôle lblPrixTest//
public static string lblPrixTest;
// Contrôle Label43//
public static string Label43;
// Contrôle Label49//
public static string Label49;
// Contrôle txtTempsInstallationSoum//
public static string txtTempsInstallationSoum;
// Contrôle txtTempsInstallationProj//
public static string txtTempsInstallationProj;
// Contrôle txtTempsInstallationConc//
public static string txtTempsInstallationConc;
// Contrôle lblTempsInstallationReel//
public static string lblTempsInstallationReel;
// Contrôle Label12//
public static string Label12;
// Contrôle lblPrixInstallation//
public static string lblPrixInstallation;
// Contrôle Label65//
public static string Label65;
// Contrôle Label41//
public static string Label41;
// Contrôle txtTempsFormationSoum//
public static string txtTempsFormationSoum;
// Contrôle txtTempsFormationProj//
public static string txtTempsFormationProj;
// Contrôle txtTempsFormationConc//
public static string txtTempsFormationConc;
// Contrôle lblTempsFormationReel//
public static string lblTempsFormationReel;
// Contrôle Label10//
public static string Label10;
// Contrôle lblPrixFormation//
public static string lblPrixFormation;
// Contrôle Label59//
public static string Label59;
// Contrôle Label67//
public static string Label67;
// Contrôle txtTempsGestionSoum//
public static string txtTempsGestionSoum;
// Contrôle txtTempsGestionProj//
public static string txtTempsGestionProj;
// Contrôle txtTempsGestionConc//
public static string txtTempsGestionConc;
// Contrôle lblTempsGestionReel//
public static string lblTempsGestionReel;
// Contrôle Label47//
public static string Label47;
// Contrôle lblPrixGestion//
public static string lblPrixGestion;
// Contrôle Label39//
public static string Label39;
// Contrôle Label53//
public static string Label53;
// Contrôle txtTempsShippingSoum//
public static string txtTempsShippingSoum;
// Contrôle txtTempsShippingProj//
public static string txtTempsShippingProj;
// Contrôle txtTempsShippingConc//
public static string txtTempsShippingConc;
// Contrôle lblTempsShippingReel//
public static string lblTempsShippingReel;
// Contrôle Label50//
public static string Label50;
// Contrôle lblPrixShipping//
public static string lblPrixShipping;
// Contrôle Label20//
public static string Label20;
// Contrôle Label60//
public static string Label60;
// Contrôle txtTempsPrototypeSoum//
public static string txtTempsPrototypeSoum;
// Contrôle txtTempsPrototypeProj//
public static string txtTempsPrototypeProj;
// Contrôle txtTempsPrototypeConc//
public static string txtTempsPrototypeConc;
// Contrôle lblTempsPrototypeReel//
public static string lblTempsPrototypeReel;
// Contrôle Label23//
public static string Label23;
// Contrôle lblPrixPrototype//
public static string lblPrixPrototype;
// Contrôle Label17//
public static string Label17;
// Contrôle Label52//
public static string Label52;
// Contrôle lblTotalTempsRHSoum//
public static string lblTotalTempsRHSoum;
// Contrôle lblTotalTempsRHProj//
public static string lblTotalTempsRHProj;
// Contrôle lblTotalTempsRHConc//
public static string lblTotalTempsRHConc;
// Contrôle lblTotalTempsRHReel//
public static string lblTotalTempsRHReel;
// Contrôle Label11//
public static string Label11;
// Contrôle lblTotalPrixRH//
public static string lblTotalPrixRH;
// Contrôle lblDollarRH//
public static string lblDollarRH;
// Contrôle cmdDetail//
public static string cmdDetail;
// Contrôle lblFormTitle//
public static string lblFormTitle;
// Contrôle fraFraisSubsistences//
public static string fraFraisSubsistences;
// Contrôle lblfraFraisSubsistences//
public static string lblfraFraisSubsistences;
// Contrôle Label38//
public static string Label38;
// Contrôle Label46//
public static string Label46;
// Contrôle txtNbrePersonne//
public static string txtNbrePersonne;
// Contrôle Label31//
public static string Label31;
// Contrôle txtTempsHebergement//
public static string txtTempsHebergement;
// Contrôle Label36//
public static string Label36;
// Contrôle lblPrixHebergement//
public static string lblPrixHebergement;
// Contrôle Label27//
public static string Label27;
// Contrôle Label45//
public static string Label45;
// Contrôle txtTempsRepas//
public static string txtTempsRepas;
// Contrôle Label37//
public static string Label37;
// Contrôle lblPrixRepas//
public static string lblPrixRepas;
// Contrôle Label29//
public static string Label29;
// Contrôle Label44//
public static string Label44;
// Contrôle txtTempsDeplacement//
public static string txtTempsDeplacement;
// Contrôle Label35//
public static string Label35;
// Contrôle lblPrixDeplacement//
public static string lblPrixDeplacement;
// Contrôle Label28//
public static string Label28;
// Contrôle Label42//
public static string Label42;
// Contrôle txtTempsUniteMobile//
public static string txtTempsUniteMobile;
// Contrôle Label34//
public static string Label34;
// Contrôle lblPrixUniteMobile//
public static string lblPrixUniteMobile;
// Contrôle Label40//
public static string Label40;
// Contrôle fraManutention//
public static string fraManutention;
// Contrôle lblfraManutention//
public static string lblfraManutention;
// Contrôle Label33//
public static string Label33;
// Contrôle Label24//
public static string Label24;
// Contrôle txtPrixEmballage//
public static string txtPrixEmballage;
// Contrôle Label48//
public static string Label48;
// Contrôle cmdUnlock//
public static string cmdUnlock;
// Contrôle cmdLock//
public static string cmdLock;
// Contrôle Label25//
public static string Label25;
// Contrôle lblTotal//
public static string lblTotal;
// Contrôle Label26//
public static string Label26;
public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public class DR_Reception
{
public static bool Orientation;

public static string lblTitre;

//TitreNumero//
public static string TitreNumero;
//lblDate//
public static string lblDate;
//lblTitreProjetAchat//
public static string lblTitreProjetAchat;
//lblProjetAchat//
public static string lblProjetAchat;
//GridView1//
//Label8//
public static string Label8;
//lblTotal//
public static string lblTotal;
}
public class DR_Retour
{
public static string Button1;
public static string Impression;
public static string lblTitreCommande;
public static string lblTitreFournisseur;
public static string lblFournisseur;
public static string lblTitreProjet;
public static string lblNoProjet;
public static string lblTitreRMA;
public static string lblNoRMA;
public static string lblTitreDate;
public static string lblDate;
public static string lblTitreTransport;
public static string TextBox5;
public static string lblTitreExpiditeur;
public static string TextBox4;
public static string Label3;
public static string TextBox3;
public static string lblTitreRecepteur;
public static string TextBox2;
public static string lblTitreDateReception; //"Date: ";
public static string TextBox1;
public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public partial class DR_SommaireHeures
{//Impression//
public static string Impression;
//lblTitreDateDebut//
public static string lblTitreDateDebut;
//lblDateDebut//
public static string lblDateDebut;
//lblTitreDateFin//
public static string lblTitreDateFin;
//lblDateFin//
public static string lblDateFin;
//Label1//
public static string Label1;
//lblTitreHeures//
public static string lblTitreHeures;
//lblTitreSoumElec//
public static string lblTitreSoumElec;
//lblSoumElec//
public static string lblSoumElec;
//lblTitreSoumMec//
public static string lblTitreSoumMec;
//lblSoumMec//
public static string lblSoumMec;
//lblTitreVide0//
public static string lblTitreVide0;
//lblVide0//
public static string lblVide0;
//lblTitreTotalSoum//
public static string lblTitreTotalSoum;
//lblTotalSoum//
public static string lblTotalSoum;
//lblTitreVide1//
public static string lblTitreVide1;
//lblVide1//
public static string lblVide1;
//lblTitreProjGRBElec//
public static string lblTitreProjGRBElec;
//lblProjGRBElec//
public static string lblProjGRBElec;
//lblTitreProjGRBMec//
public static string lblTitreProjGRBMec;
//lblProjGRBMec//
public static string lblProjGRBMec;
//lblTitreVide2//
public static string lblTitreVide2;
//lblVide2//
public static string lblVide2;
//lblTitreTotalProjGRB//
public static string lblTitreTotalProjGRB;
//lblTotalProjGRB//
public static string lblTotalProjGRB;
//lblTitreVide3//
public static string lblTitreVide3;
//lblVide3//
public static string lblVide3;
//lblTitreProjElec//
public static string lblTitreProjElec;
//lblProjElec//
public static string lblProjElec;
//lblTitreProjMec//
public static string lblTitreProjMec;
//lblProjMec//
public static string lblProjMec;
//lblTitreVide4//
public static string lblTitreVide4;
//lblVide4//
public static string lblVide4;
//lblTitreTotalProj//
public static string lblTitreTotalProj;
//lblTotalProj//
public static string lblTotalProj;
//lblTitreVide5//
public static string lblTitreVide5;
//lblVide5//
public static string lblVide5;
//lblTitreFabElec//
public static string lblTitreFabElec;
//lblFabElec//
public static string lblFabElec;
//lblTitreFabMec//
public static string lblTitreFabMec;
//lblFabMec//
public static string lblFabMec;
//lblTitreVide6//
public static string lblTitreVide6;
//lblVide6//
public static string lblVide6;
//lblTitreTotalFab//
public static string lblTitreTotalFab;
//lbTotalFab//
public static string lbTotalFab;
//lblTitreVide7//
public static string lblTitreVide7;
//lblVide7//
public static string lblVide7;
//lblTitreRechElec//
public static string lblTitreRechElec;
//lblRechElec//
public static string lblRechElec;
//lblTitreRechMec//
public static string lblTitreRechMec;
//lblRechMec//
public static string lblRechMec;
//lblTitreVide8//
public static string lblTitreVide8;
//lblVide8//
public static string lblVide8;
//lblTitreTotalRech//
public static string lblTitreTotalRech;
//lblTotalRech//
public static string lblTotalRech;
//lblTitreVide9//
public static string lblTitreVide9;
//lblVide9//
public static string lblVide9;
//lblTitreAppelsElec//
public static string lblTitreAppelsElec;
//lblAppelsElec//
public static string lblAppelsElec;
//lblTitreAppelsMec//
public static string lblTitreAppelsMec;
//lblAppelsMec//
public static string lblAppelsMec;
//lblTitreVide10//
public static string lblTitreVide10;
//lblVide10//
public static string lblVide10;
//lblTitreTotalAppels//
public static string lblTitreTotalAppels;
//lblTotalAppels//
public static string lblTotalAppels;
//lblTitreVide11//
public static string lblTitreVide11;
//lblVide11//
public static string lblVide11;
//lblTitreGrandTotal//
public static string lblTitreGrandTotal;
//lblGrandTotal//
public static string lblGrandTotal;
public static string lblTotalFab;
public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public partial class DR_SommairePunchGRB
{



public static string EnTeteAdresse;



//EnTeteTelFax.





//
public static string EnTeteTelFax;



//Label15.





//
public static string Label15;



//lblDateDebut.





//
public static string lblDateDebut;



//Label17.





//
public static string Label17;



//lblDateFin.





//
public static string lblDateFin;



//Label3.





//
public static string Label3;



//Label4.





//
public static string Label4;



//Label2.





//
public static string Label2;



//Label5.





//
public static string Label5;



//Label6.





//
public static string Label6;



//Label7.





//
public static string Label7;



//Label9.





//
public static string Label9;



//Label12.





//
public static string Label12;



//txtNomJour.





//
public static string txtNomJour;



//txtProjet.





//
public static string txtProjet;



//Text1.





//
public static string Text1;



//txtDescription.





//
public static string txtDescription;



//txtJournee.





//
public static string txtJournee;



//txtA.





//
public static string txtA;



//txtTotal.





//
public static string txtTotal;



//Text2.





//
public static string Text2;



//GridView1.









//Label0.





//
public static string Label0;



//lblGrandTotal.





//
public static string lblGrandTotal;



//Label13.





//
public static string Label13;



//lblGrandTotalKM.





//
public static string lblGrandTotalKM;



//Label8.





//
public static string Label8;
public static bool Orientation = !WebGRB2024.Program.isLandscape;

}
public partial class DR_SoumissionElec
{
//Button2//
public static string Button2;
//Impression//
public static string Impression;
//EnTeteLogo//

//EnTeteAdresse//
public static string EnTeteAdresse;
//EnTeteTelFax//
public static string EnTeteTelFax;
//lblTitre//
public static string lblTitre;
//lblTitreProjet//
public static string lblTitreProjet;
//lblProjet//
public static string lblProjet;
//lblTitreSoumission//
public static string lblTitreSoumission;
//lblSoumission//
public static string lblSoumission;
//Label3//
public static string Label3;
//lblDescription//
public static string lblDescription;
//lblTitreClient//
public static string lblTitreClient;
//lblClient//
public static string lblClient;
//lblTitreFacture//
public static string lblTitreFacture;
//lblFacture//
public static string lblFacture;
//lblTitreContact//
public static string lblTitreContact;
//lblContact//
public static string lblContact;
//lblTitreQuantite//
public static string lblTitreQuantite;
//lblTitreNoItem//
public static string lblTitreNoItem;
//lblTitreDescription//
public static string lblTitreDescription;
//lblTitreManufacturier//
public static string lblTitreManufacturier;
//lblTitreCoutant//
public static string lblTitreCoutant;
//lblTitreFournisseur//
public static string lblTitreFournisseur;
//lblTitreTotal//
public static string lblTitreTotal;
//lblTitreProfit//
public static string lblTitreProfit;
//lbl_DateCommande//
public static string lbl_DateCommande;
//lbl_DateReception//
public static string lbl_DateReception;
//Text1//
public static string Text1;
//Text2//
public static string Text2;
//Text14//
public static string Text14;
//Text3//
public static string Text3;
//Text12//
public static string Text12;
//Text4//
public static string Text4;
//Text7//
public static string Text7;
//Text8//
public static string Text8;
//Text11//
public static string Text11;
//Text13//
public static string Text13;
//txt_DateCommande//
public static string txt_DateCommande;
//txt_DateReception//
public static string txt_DateReception;
//lblTitreTemps//
public static string lblTitreTemps;
//lblTitreTauxHoraire//
public static string lblTitreTauxHoraire;
//Label40//
public static string Label40;
//lblTitreDessin//
public static string lblTitreDessin;
//lblTauxDessin//
public static string lblTauxDessin;
//lblTempsDessinSoum//
public static string lblTempsDessinSoum;
//lblTempsDessinReel//
public static string lblTempsDessinReel;
//lblHeure1//
public static string lblHeure1;
//lblTitreFabrication//
public static string lblTitreFabrication;
//lblTauxFabrication//
public static string lblTauxFabrication;
//lblTempsFabrication//
public static string lblTempsFabrication;
//lblTempsFabricationReel//
public static string lblTempsFabricationReel;
//lblHeure2//
public static string lblHeure2;
//lblTitreAssemblage//
public static string lblTitreAssemblage;
//lblTauxAssemblage//
public static string lblTauxAssemblage;
//lblTempsAssemblageSoum//
public static string lblTempsAssemblageSoum;
//lblTempsAssemblageReel//
public static string lblTempsAssemblageReel;
//lblHeure3//
public static string lblHeure3;
//lblTitreProgInterface//
public static string lblTitreProgInterface;
//lblTauxProgInterface//
public static string lblTauxProgInterface;
//lblTempsProgInterfaceSoum//
public static string lblTempsProgInterfaceSoum;
//Label21//
public static string Label21;
//lblHeure4//
public static string lblHeure4;
//lblTitreProgAutomate//
public static string lblTitreProgAutomate;
//lblTauxProgAutomate//
public static string lblTauxProgAutomate;
//lblTempsProgAutomateSoum//
public static string lblTempsProgAutomateSoum;
//lblTempsProgAutomateReel//
public static string lblTempsProgAutomateReel;
//lblHeure5//
public static string lblHeure5;
//lblTitreProgRobot//
public static string lblTitreProgRobot;
//lblTauxProgRobot//
public static string lblTauxProgRobot;
//lblTempsProgRobotSoum//
public static string lblTempsProgRobotSoum;
//lblTempsProgRobotReel//
public static string lblTempsProgRobotReel;
//lblHeure6//
public static string lblHeure6;
//lblTitreVision//
public static string lblTitreVision;
//lblTauxVision//
public static string lblTauxVision;
//lblTempsVisionSoum//
public static string lblTempsVisionSoum;
//lblTempsVisionReel//
public static string lblTempsVisionReel;
//lblHeure7//
public static string lblHeure7;
//lblTitreTest//
public static string lblTitreTest;
//lblTauxTest//
public static string lblTauxTest;
//lblTempsTestSoum//
public static string lblTempsTestSoum;
//lblTempsTestReel//
public static string lblTempsTestReel;
//lblHeure8//
public static string lblHeure8;
//lblTitreInstallation//
public static string lblTitreInstallation;
//lblTauxInstallation//
public static string lblTauxInstallation;
//lblTempsInstallationSoum//
public static string lblTempsInstallationSoum;
//lblTempsInstallationReel//
public static string lblTempsInstallationReel;
//lblHeure9//
public static string lblHeure9;
//lblTitreMiseService//
public static string lblTitreMiseService;
//lblTauxMiseService//
public static string lblTauxMiseService;
//lblTempsMiseServiceSoum//
public static string lblTempsMiseServiceSoum;
//lblTempsMiseServiceReel//
public static string lblTempsMiseServiceReel;
//lblHeure11//
public static string lblHeure11;
//lblTitreFormation//
public static string lblTitreFormation;
//lblTauxFormation//
public static string lblTauxFormation;
//lblTempsFormationSoum//
public static string lblTempsFormationSoum;
//lblTempsFormationReel//
public static string lblTempsFormationReel;
//lblHeure12//
public static string lblHeure12;
//lblTitreGestion//
public static string lblTitreGestion;
//lblTauxGestion//
public static string lblTauxGestion;
//lblTempsGestionSoum//
public static string lblTempsGestionSoum;
//lblTempsGestionReel//
public static string lblTempsGestionReel;
//lblHeure13//
public static string lblHeure13;
//lblTitreShipping//
public static string lblTitreShipping;
//lblTauxShipping//
public static string lblTauxShipping;
//lblTempsShippingSoum//
public static string lblTempsShippingSoum;
//lblTempsShippingReel//
public static string lblTempsShippingReel;
//lblHeure14//
public static string lblHeure14;
//lblTotalTempsRHSoum//
public static string lblTotalTempsRHSoum;
//lblTotalTempsRHReel//
public static string lblTotalTempsRHReel;
//lblHeure10//
public static string lblHeure10;
//lblTitreNbrePersonne//
public static string lblTitreNbrePersonne;
//lblNbrePersonne//
public static string lblNbrePersonne;
//lblTitreHebergement1//
public static string lblTitreHebergement1;
//lblTauxHebergement1//
public static string lblTauxHebergement1;
//lblTempsHebergement//
public static string lblTempsHebergement;
//lblJour1//
public static string lblJour1;
//Label1//
public static string Label1;
//lblTauxHebergement2//
public static string lblTauxHebergement2;
//lblTitreRepas//
public static string lblTitreRepas;
//lblTauxRepas//
public static string lblTauxRepas;
//lblTempsRepas//
public static string lblTempsRepas;
//lblJour2//
public static string lblJour2;
//lblTitreTransportDeplacement//
public static string lblTitreTransportDeplacement;
//lblTauxTransport//
public static string lblTauxTransport;
//lblTempsTransport//
public static string lblTempsTransport;
//Label46//
public static string Label46;
//lblTitreTransportUniteMobile//
public static string lblTitreTransportUniteMobile;
//lblTauxUniteMobile//
public static string lblTauxUniteMobile;
//lblTempsUniteMobile//
public static string lblTempsUniteMobile;
//Label47//
public static string Label47;
//lblTitreTransportEmballage//
public static string lblTitreTransportEmballage;
//lblPrixEmballage//
public static string lblPrixEmballage;
//Label4//
public static string Label4;
//lblPrixManuel//
public static string lblPrixManuel;
//lblTitreTotalPiece//
public static string lblTitreTotalPiece;
//lblTotalPieceAR//
public static string lblTotalPieceAR;
//lblTitreProfitGlobal//
public static string lblTitreProfitGlobal;
//lblProfit//
public static string lblProfit;
//lblTotalProfit//
public static string lblTotalProfit;
//lblTitreImprevue//
public static string lblTitreImprevue;
//lblImprevue//
public static string lblImprevue;
//lblImprevueAR//
public static string lblImprevueAR;
//lblTitreTotalTemps//
public static string lblTitreTotalTemps;
//lblTotalTempsAR//
public static string lblTotalTempsAR;
//lblTitreAutre//
public static string lblTitreAutre;
//lblAutre//
public static string lblAutre;
//lblTitreCommission//
public static string lblTitreCommission;
//lblCommission//
public static string lblCommission;
//lblcommissionAR//
public static string lblcommissionAR;
//lblTitreGrandTotal//
public static string lblTitreGrandTotal;
//lblGrandTotalAR//
public static string lblGrandTotalAR;
//lblTitrePrixReception//
public static string lblTitrePrixReception;
//lblTitrePrixSoumission//
public static string lblTitrePrixSoumission;
//lblTitreForfait//
public static string lblTitreForfait;
//lblPrixReception//
public static string lblPrixReception;
//lblPrixSoumission//
public static string lblPrixSoumission;
//lblForfait//
public static string lblForfait;
public static bool shpCadrePrixReceptionVisible;
public static bool lblTitrePrixReceptionVisible;
public static bool lblPrixReceptionVisible;
public static bool shpCadrePrixSoumissionVisible;
public static bool lblTitrePrixSoumissionVisible;
public static bool lblPrixSoumissionVisible;
public static string lbldateCaption;
public static dynamic lblSoumissionCaption;
public static string lblProjetCaption;
public static dynamic lbldescriptionCaption;
public static dynamic lblclientCaption;
public static dynamic lblTempsFabricationSoum;
public static dynamic lblCommissionAR;
public static bool shpCadreForfaitVisible;
public static bool lblTitreForfaitVisible;
public static bool lblForfaitVisible;
public static string lblTitreForfaitCaption;
public static bool lbl_DateCommandeVisible;
public static bool lbl_DateReceptionVisible;
public static bool txt_DateCommandeVisible;
public static bool txt_DateReceptionVisible;
public static string lblTempsProgInterfaceReel;
public static bool lblTitreNoFactureVisible;
public static bool lblNoFactureVisible;
public static string lblNoFacture;
public static string lblGrosTitre;
public static string lblNoPage;
public static Recordset DataSource;
public static bool Orientation = !WebGRB2024.Program.isLandscape;
}
public partial class DR_SoumissionMec
{
public static string EnTeteAdresse;

//EnTeteTelFax.//
public static string EnTeteTelFax;

//lblTitre.//
public static string lblTitre;

//lblTitreProjet.//
public static string lblTitreProjet;

//lblProjet.//
public static string lblProjet;

//lblTitreSoumission.//
public static string lblTitreSoumission;

//lblSoumission.//
public static string lblSoumission;

//Label3.//
public static string Label3;

//lblDescription.//
public static string lblDescription;

//lblTitreClient.//
public static string lblTitreClient;

//lblClient.//
public static string lblClient;

//lblTitreFacture.//
public static string lblTitreFacture;

//lblFacture.//
public static string lblFacture;

//lblTitreContact.//
public static string lblTitreContact;

//lblContact.//
public static string lblContact;

//lblTitreQuantite.//
public static string lblTitreQuantite;

//lblTitreNoItem.//
public static string lblTitreNoItem;

//lblTitreDescription.//
public static string lblTitreDescription;

//lblTitreManufacturier.//
public static string lblTitreManufacturier;

//lblTitreCoutant.//
public static string lblTitreCoutant;

//lblTitreFournisseur.//
public static string lblTitreFournisseur;

//lblTitreTotal.//
public static string lblTitreTotal;

//lblTitreProfit.//
public static string lblTitreProfit;

//lbl_DateCommande.//
public static string lbl_DateCommande;

//lbl_DateReception.//
public static string lbl_DateReception;

//Text1.//
public static string Text1;

//Text2.//
public static string Text2;

//Text14.//
public static string Text14;

//Text3.//
public static string Text3;

//Text12.//
public static string Text12;

//Text4.//
public static string Text4;

//Text7.//
public static string Text7;

//Text8.//
public static string Text8;

//Text11.//
public static string Text11;

//Text13.//
public static string Text13;

//txt_DateCommande.//
public static string txt_DateCommande;

//txt_DateReception.//
public static string txt_DateReception;

//GridView1.

//lblTitreTemps.//
public static string lblTitreTemps;

//lblTitreTauxHoraire.//
public static string lblTitreTauxHoraire;

//Label40.//
public static string Label40;

//lblTitreDessin.//
public static string lblTitreDessin;

//lblTauxDessin.//
public static string lblTauxDessin;

//lblTempsDessinSoum.//
public static string lblTempsDessinSoum;

//lblTempsDessinReel.//
public static string lblTempsDessinReel;

//lblHeure1.//
public static string lblHeure1;

//lblTitreFabrication.//
public static string lblTitreFabrication;

//lblTauxFabrication.//
public static string lblTauxFabrication;

//lblTempsFabrication.//
public static string lblTempsFabrication;

//lblTempsFabricationReel.//
public static string lblTempsFabricationReel;

//lblHeure2.//
public static string lblHeure2;

//lblTitreAssemblage.//
public static string lblTitreAssemblage;

//lblTauxAssemblage.//
public static string lblTauxAssemblage;

//lblTempsAssemblageSoum.//
public static string lblTempsAssemblageSoum;

//lblTempsAssemblageReel.//
public static string lblTempsAssemblageReel;

//lblHeure3.//
public static string lblHeure3;

//lblTitreProgInterface.//
public static string lblTitreProgInterface;

//lblTauxProgInterface.//
public static string lblTauxProgInterface;

//lblTempsProgInterfaceSoum.//
public static string lblTempsProgInterfaceSoum;

//Label21.//
public static string Label21;

//lblHeure4.//
public static string lblHeure4;

//lblTitreProgAutomate.//
public static string lblTitreProgAutomate;

//lblTauxProgAutomate.//
public static string lblTauxProgAutomate;

//lblTempsProgAutomateSoum.//
public static string lblTempsProgAutomateSoum;

//lblTempsProgAutomateReel.//
public static string lblTempsProgAutomateReel;

//lblHeure5.//
public static string lblHeure5;

//lblTitreProgRobot.//
public static string lblTitreProgRobot;

//lblTauxProgRobot.//
public static string lblTauxProgRobot;

//lblTempsProgRobotSoum.//
public static string lblTempsProgRobotSoum;

//lblTempsProgRobotReel.//
public static string lblTempsProgRobotReel;

//lblHeure6.//
public static string lblHeure6;

//lblTitreVision.//
public static string lblTitreVision;

//lblTauxVision.//
public static string lblTauxVision;

//lblTempsVisionSoum.//
public static string lblTempsVisionSoum;

//lblTempsVisionReel.//
public static string lblTempsVisionReel;

//lblHeure7.//
public static string lblHeure7;

//lblTitreTest.//
public static string lblTitreTest;

//lblTauxTest.//
public static string lblTauxTest;

//lblTempsTestSoum.//
public static string lblTempsTestSoum;

//lblTempsTestReel.//
public static string lblTempsTestReel;

//lblHeure8.//
public static string lblHeure8;

//lblTitreInstallation.//
public static string lblTitreInstallation;

//lblTauxInstallation.//
public static string lblTauxInstallation;

//lblTempsInstallationSoum.//
public static string lblTempsInstallationSoum;

//lblTempsInstallationReel.//
public static string lblTempsInstallationReel;

//lblHeure9.//
public static string lblHeure9;

//lblTitreMiseService.//
public static string lblTitreMiseService;

//lblTauxMiseService.//
public static string lblTauxMiseService;

//lblTempsMiseServiceSoum.//
public static string lblTempsMiseServiceSoum;

//lblTempsMiseServiceReel.//
public static string lblTempsMiseServiceReel;

//lblHeure11.//
public static string lblHeure11;

//lblTitreFormation.//
public static string lblTitreFormation;

//lblTauxFormation.//
public static string lblTauxFormation;

//lblTempsFormationSoum.//
public static string lblTempsFormationSoum;

//lblTempsFormationReel.//
public static string lblTempsFormationReel;

//lblHeure12.//
public static string lblHeure12;

//lblTitreGestion.//
public static string lblTitreGestion;

//lblTauxGestion.//
public static string lblTauxGestion;

//lblTempsGestionSoum.//
public static string lblTempsGestionSoum;

//lblTempsGestionReel.//
public static string lblTempsGestionReel;

//lblHeure13.//
public static string lblHeure13;

//lblTitreShipping.//
public static string lblTitreShipping;

//lblTauxShipping.//
public static string lblTauxShipping;

//lblTempsShippingSoum.//
public static string lblTempsShippingSoum;

//lblTempsShippingReel.//
public static string lblTempsShippingReel;

//lblHeure14.//
public static string lblHeure14;

//lblTotalTempsRHSoum.//
public static string lblTotalTempsRHSoum;

//lblTotalTempsRHReel.//
public static string lblTotalTempsRHReel;

//lblHeure10.//
public static string lblHeure10;

//lblTitreNbrePersonne.//
public static string lblTitreNbrePersonne;

//lblNbrePersonne.//
public static string lblNbrePersonne;

//lblTitreHebergement1.//
public static string lblTitreHebergement1;

//lblTauxHebergement1.//
public static string lblTauxHebergement1;

//lblTempsHebergement.//
public static string lblTempsHebergement;

//lblJour1.//
public static string lblJour1;

//Label1.//
public static string Label1;

//lblTauxHebergement2.//
public static string lblTauxHebergement2;

//lblTitreRepas.//
public static string lblTitreRepas;

//lblTauxRepas.//
public static string lblTauxRepas;

//lblTempsRepas.//
public static string lblTempsRepas;

//lblJour2.//
public static string lblJour2;

//lblTitreTransportDeplacement.//
public static string lblTitreTransportDeplacement;

//lblTauxTransport.//
public static string lblTauxTransport;

//lblTempsTransport.//
public static string lblTempsTransport;

//Label46.//
public static string Label46;

//lblTitreTransportUniteMobile.//
public static string lblTitreTransportUniteMobile;

//lblTauxUniteMobile.//
public static string lblTauxUniteMobile;

//lblTempsUniteMobile.//
public static string lblTempsUniteMobile;

//Label47.//
public static string Label47;

//lblTitreTransportEmballage.//
public static string lblTitreTransportEmballage;

//lblPrixEmballage.//
public static string lblPrixEmballage;

//Label4.//
public static string Label4;

//lblPrixManuel.//
public static string lblPrixManuel;

//lblTitreTotalPiece.//
public static string lblTitreTotalPiece;

//lblTotalPieceAR.//
public static string lblTotalPieceAR;

//lblTitreProfitGlobal.//
public static string lblTitreProfitGlobal;

//lblProfit.//
public static string lblProfit;

//lblTotalProfit.//
public static string lblTotalProfit;

//lblTitreImprevue.//
public static string lblTitreImprevue;

//lblImprevue.//
public static string lblImprevue;

//lblImprevueAR.//
public static string lblImprevueAR;

//lblTitreTotalTemps.//
public static string lblTitreTotalTemps;

//lblTotalTempsAR.//
public static string lblTotalTempsAR;

//lblTitreAutre.//
public static string lblTitreAutre;

//lblAutre.//
public static string lblAutre;

//lblTitreCommission.//
public static string lblTitreCommission;

//lblCommission.//
public static string lblCommission;

//lblcommissionAR.//
public static string lblcommissionAR;

//lblTitreGrandTotal.//
public static string lblTitreGrandTotal;

//lblGrandTotalAR.//
public static string lblGrandTotalAR;

//lblTitrePrixReception.//
public static string lblTitrePrixReception;

//lblTitrePrixSoumission.//
public static string lblTitrePrixSoumission;

//lblTitreForfait.//
public static string lblTitreForfait;

//lblPrixReception.//
public static string lblPrixReception;

//lblPrixSoumission.//
public static string lblPrixSoumission;

//lblForfait.//
public static string lblForfait;

//Label8.//
public static string Label8;
public static string lblTotalTempsRHConc;
public static string lblTempsDessinConc;
public static string lblTempsCoupeConc;
public static string lblTempsMachinageConc;
public static string lblTempsSoudureConc;
public static string lblTempsAssemblageConc;
public static string lblTempsPeintureConc;
public static string lblTempsTestConc;
public static string lblTempsInstallationConc;
public static string lblTempsFormationConc;
public static string lblTempsGestionConc;
public static string lblTempsShippingConc;
public static bool shpCadreForfaitVisible;
public static bool lblTitreForfaitVisible;
public static bool lblForfaitVisible;
public static bool lbl_DateCommandeVisible;
public static bool lbl_DateReceptionVisible;
public static bool txt_DateCommandeVisible;
public static bool txt_DateReceptionVisible;
public static string lblTempsCoupeReel;
public static string lblTempsMachinageReel;
public static string lblTempsSoudureReel;
public static string lblTempsPeintureReel;
public static string lblGrosTitre;
public static string lblTitreMachinage;
public static string lblTitreCoupePreparation;
public static string lblTitreAssemblageSoudure;
public static string lblTitreAssemblageSysteme;
public static string lblTitrePeintureFinition;
public static string lblTitreTestFinal;
public static string lblTitreConceptionDessin;
public static string lblTitreHebergement2;
public static string lblNoPage;
public static bool shpCadrePrixReceptionVisible;
public static bool lblTitrePrixReceptionVisible;
public static bool lblPrixReceptionVisible;
public static string lblTauxCoupe;
public static string lbldate;
public static bool lblNoFactureVisible;
public static bool lblTitreNoFactureVisible;
public static bool shpCadrePrixSoumissionVisible;
public static bool lblTitrePrixSoumissionVisible;
public static bool lblPrixSoumissionVisible;
public static string lblNoFacture;
public static string lblTauxMachinage;
public static string lblTempsDessinProj;
public static string lblTempsCoupeProj;
public static string lblTempsMachinageProj;
public static string lblTempsSoudureProj;
public static string lblTempsAssemblageProj;
public static string lblTempsPeintureProj;
public static string lblTempsTestProj;
public static string lblTempsInstallationProj;
public static string lblTempsFormationProj;
public static string lblTempsGestionProj;
public static string lblTempsShippingProj;
public static string lblTotalTempsRHProj;
public static string lblTauxPeinture;
public static string lblTauxSoudure;
public static string lblTempsCoupeSoum;
public static string lblTempsMachinageSoum;
public static string lblTempsSoudureSoum;
public static string lblTempsPeintureSoum;

public static bool Orientation = !WebGRB2024.Program.isLandscape;
public static string Text { get; set; }
public static Recordset DataSource { get; set; }
}
public partial class DR_TempsElec
{
public static string EnTeteAdresse;        
//EnTeteTelFax*/
public static string EnTeteTelFax;        
//Label24*/
public static string Label24;        
//lblNoProjet*/
public static string lblNoProjet;        
//Label2*/
public static string Label2;        
//Label23*/
public static string Label23;        
//Label32*/
public static string Label32;        
//Label4*/
public static string Label4;        
//lblTempsDessinEstime*/
public static string lblTempsDessinEstime;        
//lblTempsDessinReel*/
public static string lblTempsDessinReel;        
//Label11*/
public static string Label11;        
//Label5*/
public static string Label5;        
//lblTempsFabricationEstime*/
public static string lblTempsFabricationEstime;        
//lblTempsFabricationReel*/
public static string lblTempsFabricationReel;        
//Label12*/
public static string Label12;        
//Label6*/
public static string Label6;        
//lblTempsAssemblageEstime*/
public static string lblTempsAssemblageEstime;        
//lblTempsAssemblageReel*/
public static string lblTempsAssemblageReel;        
//Label13*/
public static string Label13;        
//Label7*/
public static string Label7;        
//lblTempsProgInterfaceEstime*/
public static string lblTempsProgInterfaceEstime;        
//lblTempsProgInterfaceReel*/
public static string lblTempsProgInterfaceReel;        
//Label14*/
public static string Label14;        
//Label8*/
public static string Label8;        
//lblTempsProgAutomateEstime*/
public static string lblTempsProgAutomateEstime;        
//lblTempsProgAutomateReel*/
public static string lblTempsProgAutomateReel;        
//Label15*/
public static string Label15;        
//Label9*/
public static string Label9;        
//lblTempsProgRobotEstime*/
public static string lblTempsProgRobotEstime;        
//lblTempsProgRobotReel*/
public static string lblTempsProgRobotReel;        
//Label16*/
public static string Label16;        
//Label33*/
public static string Label33;        
//lblTempsVisionEstime*/
public static string lblTempsVisionEstime;        
//lblTempsVisionReel*/
public static string lblTempsVisionReel;        
//Label35*/
public static string Label35;        
//Label37*/
public static string Label37;        
//lblTempsTestEstime*/
public static string lblTempsTestEstime;        
//lblTempsTestReel*/
public static string lblTempsTestReel;        
//Label39*/
public static string Label39;        
//Label41*/
public static string Label41;        
//lblTempsInstallationEstime*/
public static string lblTempsInstallationEstime;        
//lblTempsInstallationReel*/
public static string lblTempsInstallationReel;        
//Label43*/
public static string Label43;        
//Label45*/
public static string Label45;        
//lblTempsMiseServiceEstime*/
public static string lblTempsMiseServiceEstime;        
//lblTempsMiseServiceReel*/
public static string lblTempsMiseServiceReel;        
//Label47*/
public static string Label47;        
//Label1*/
public static string Label1;        
//lblTempsFormationEstime*/
public static string lblTempsFormationEstime;        
//lblTempsFormationReel*/
public static string lblTempsFormationReel;        
//Label22*/
public static string Label22;        
//Label49*/
public static string Label49;        
//lblTempsGestionEstime*/
public static string lblTempsGestionEstime;        
//lblTempsGestionReel*/
public static string lblTempsGestionReel;        
//Label51*/
public static string Label51;        
//Label25*/
public static string Label25;        
//lblTempsShippingEstime*/
public static string lblTempsShippingEstime;        
//lblTempsShippingReel*/
public static string lblTempsShippingReel;        
//Label27*/
public static string Label27;        
//Label26*/
public static string Label26;        
//Label28*/
public static string Label28;        
//lblTempsprototypeReel*/
public static string lblTempsprototypeReel;        
//Label29*/
public static string Label29;        
//lblTitreTotalTemps*/
public static string lblTitreTotalTemps;        
//lblTotalTempsEstime*/
public static string lblTotalTempsEstime;        
//lblTotalTempsReel*/
public static string lblTotalTempsReel;        
//Label17*/
public static string Label17;        
//Label3*/
public static string Label3;        
//Label20*/
public static string Label20;        
//Label10*/
public static string Label10;        
//Label21*/
public static string Label21;        
//Text1*/
public static string Text1;        
//Text3*/
public static string Text3;        
//Text2*/
public static string Text2;
public static Recordset DataSource;
}
public class DR_TempsMec
{
internal static string lblNoProjet;
internal static string lblTempsDessinSoum;
internal static string lblTempsCoupeSoum;
internal static string lblTempsMachinageSoum;
internal static string lblTempsSoudureSoum;
internal static string lblTempsAssemblageSoum;
internal static string lblTempsPeintureSoum;
internal static string lblTempsTestSoum;
internal static string lblTempsInstallationSoum;
internal static string lblTempsFormationSoum;
internal static string lblTempsGestionSoum;
internal static string lblTempsShippingSoum;
internal static string lblTempsDessinProj;
internal static string lblTempsCoupeProj;
internal static string lblTempsMachinageProj;
internal static string lblTempsSoudureProj;
internal static string lblTempsAssemblageProj;
internal static string lblTempsPeintureProj;
internal static string lblTempsTestProj;
internal static string lblTempsInstallationProj;
internal static string lblTempsFormationProj;
internal static string lblTempsGestionProj;
internal static string lblTempsShippingProj;
internal static string lblTempsDessinConc;
internal static string lblTempsCoupeConc;
internal static string lblTempsMachinageConc;
internal static string lblTempsSoudureConc;
internal static string lblTempsAssemblageConc;
internal static string lblTempsPeintureConc;
internal static string lblTempsTestConc;
internal static string lblTempsInstallationConc;
internal static string lblTempsFormationConc;
internal static string lblTempsGestionConc;
internal static string lblTempsShippingConc;
internal static string lblTotalTempsSoum;
internal static string lblTotalTempsProj;
internal static string lblTotalTempsConc;
internal static string lblTempsDessinReel;
internal static string lblTempsCoupeReel;
internal static string lblTempsMachinageReel;
internal static string lblTempsSoudureReel;
internal static string lblTempsAssemblageReel;
internal static string lblTempsPeintureReel;
internal static string lblTempsTestReel;
internal static string lblTempsInstallationReel;
internal static string lblTempsFormationReel;
internal static string lblTempsGestionReel;
internal static string lblTempsShippingReel;
internal static string lblTempsprototypeReel;
internal static dynamic lblTempsPrototypeReel;
internal static string lblTotalTempsReel;
internal static string lblTitreRapport;
internal static string Label24;
internal static string TextBox1;
internal static string lblTitreTemps;
internal static string lblTempsSoum; 
//Soum.";
internal static string lblTempsProj; 
//Proj.";
internal static string lblTempsConc; 
//Conc.";
internal static string lblTempsReel; 
//Reels";
internal static string Label4; 
//Temps de dessin: ";
internal static string lblTempsDessinEstime;
internal static string TextBox2;
internal static string TextBox58;
internal static string TextBox59;
internal static string Label11; 
//hrs";
internal static string Label5; 
//Temps de fabrication: ";
internal static string TextBox4;
internal static string TextBox5;
internal static string TextBox56;
internal static string TextBox57;
internal static string Label12; 
//hrs";
internal static string Label6; 
//Temps d'assemblage: ";
internal static string TextBox6;
internal static string TextBox7;
internal static string TextBox54;
internal static string TextBox55;
internal static string Label13; 
//hrs";
internal static string Label7; 
//Temps de programmation d'interface: ";
internal static string TextBox8;
internal static string TextBox9;
internal static string TextBox52;
internal static string TextBox53;
internal static string Label14; 
//hrs";
internal static string Label8; 
//Temps de programmation d'automate: ";
internal static string TextBox3;
internal static string TextBox10;
internal static string TextBox50;
internal static string TextBox51;
internal static string Label15; 
//hrs";
internal static string Label9; 
//Temps de programmation de robot: ";
internal static string TextBox99;
internal static string TextBox49;
internal static string TextBox11;
internal static string TextBox48;
internal static string Label16; 
//hrs";
internal static string Label33; 
//Temps de vision: ";
internal static string TextBox12;
internal static string TextBox13;
internal static string TextBox46;
internal static string TextBox47;
internal static string Label35; 
//hrs";
internal static string Label37; 
//Temps de test: ";
internal static string TextBox14;
internal static string TextBox15;
internal static string TextBox44;
internal static string TextBox45;
internal static string Label39; 
//hrs";
internal static string Label41; 
//Temps d'installation: ";
internal static string TextBox16;
internal static string TextBox17;
internal static string TextBox42;
internal static string TextBox43;
internal static string Label43; 
//hrs";
internal static string Label45; 
//Temps de mise en service: ";
internal static string TextBox18;
internal static string TextBox19;
internal static string TextBox40;
internal static string TextBox41;
internal static string Label47; 
//hrs";
internal static string Label1; 
//Temps de formation du personnel: ";
internal static string TextBox20;
internal static string TextBox21;
internal static string TextBox38;
internal static string TextBox39;
internal static string Label22; 
//hrs";
internal static string Label49; 
//Temps de gestion de projet: ";
internal static string TextBox22;
internal static string TextBox23;
internal static string TextBox36;
internal static string TextBox37;
internal static string Label51; 
//hrs";
internal static string Label25; 
//Temps d'expedition: ";
internal static string TextBox24;
internal static string TextBox25;
internal static string TextBox34;
internal static string TextBox35;
internal static string Label27; 
//hrs";
internal static string Label26; 
//Prototypage: ";
internal static string TextBox32;
internal static string TextBox33;
internal static string TextBox26;
internal static string TextBox27;
internal static string Label29; 
//hrs";
internal static string lblTitreTotalTemps; 
//Total: ";
internal static string TextBox28;
internal static string TextBox29;
internal static string TextBox30;
internal static string TextBox31;
internal static string Label17; 
//hrs";
internal static string Label3; 
//Temps reels";
internal static string Label20; 
//Nom de l'employe"
internal static string Label10; 
//Type"
internal static string Label21; 
//Heure"
internal static string Text1; 
//Employe"
internal static string Text3; 
//Type"
internal static string Text2; 
//TotalHeures"
internal static string Label19; 
//%D";
internal static string Label18; 
//Page %p de %P";

internal static Recordset DataSource;
}

}