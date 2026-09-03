using System;
using System.ComponentModel.DataAnnotations.Schema;
using System.Data.Entity;
using System.Linq;

namespace WinReservations
{
    public partial class Reservations : DbContext
    {
        public Reservations()
            : base("name=Reservations")
        {
        }

        public virtual DbSet<ReservationSalle> ReservationSalle { get; set; }
        public virtual DbSet<sysdiagrams> sysdiagrams { get; set; }
        public virtual DbSet<TableSalles> TableSalles { get; set; }

        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            modelBuilder.Entity<TableSalles>()
                .HasMany(e => e.ReservationSalle)
                .WithRequired(e => e.TableSalles)
                .HasForeignKey(e => e.Salle)
                .WillCascadeOnDelete(false);
        }
    }
}
