namespace WinReservations
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel.DataAnnotations;
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Data.Entity.Spatial;

    [Table("ReservationSalle")]
    public partial class ReservationSalle
    {
        public int Id { get; set; }
        public int Salle { get; set; }
        [Required][StringLength(50)]public string AssigneeA { get; set; }
        [Required][StringLength(15)]public string Date { get; set; }
        [Required][StringLength(15)]public string Debut { get; set; }
        [Required][StringLength(15)]public string Fin { get; set; }
        public int Participants { get; set; }
        public bool Conference { get; set; }
        public bool Formation { get; set; }
        public bool Reunion { get; set; }
        public virtual TableSalles TableSalles { get; set; }
    }
}
