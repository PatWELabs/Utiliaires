USE [master]
GO

/****** Object:  Database [Reservations]    Script Date: 17/12/2023 22:59:43 ******/
CREATE DATABASE [Reservations]
 CONTAINMENT = NONE
 ON  PRIMARY 
GO

IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [Reservations].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO

ALTER DATABASE [Reservations] SET ANSI_NULL_DEFAULT OFF 
GO

ALTER DATABASE [Reservations] SET ANSI_NULLS OFF 
GO

ALTER DATABASE [Reservations] SET ANSI_PADDING OFF 
GO

ALTER DATABASE [Reservations] SET ANSI_WARNINGS OFF 
GO

ALTER DATABASE [Reservations] SET ARITHABORT OFF 
GO

ALTER DATABASE [Reservations] SET AUTO_CLOSE OFF 
GO

ALTER DATABASE [Reservations] SET AUTO_SHRINK OFF 
GO

ALTER DATABASE [Reservations] SET AUTO_UPDATE_STATISTICS ON 
GO

ALTER DATABASE [Reservations] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO

ALTER DATABASE [Reservations] SET CURSOR_DEFAULT  GLOBAL 
GO

ALTER DATABASE [Reservations] SET CONCAT_NULL_YIELDS_NULL OFF 
GO

ALTER DATABASE [Reservations] SET NUMERIC_ROUNDABORT OFF 
GO

ALTER DATABASE [Reservations] SET QUOTED_IDENTIFIER OFF 
GO

ALTER DATABASE [Reservations] SET RECURSIVE_TRIGGERS OFF 
GO

ALTER DATABASE [Reservations] SET  DISABLE_BROKER 
GO

ALTER DATABASE [Reservations] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO

ALTER DATABASE [Reservations] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO

ALTER DATABASE [Reservations] SET TRUSTWORTHY OFF 
GO

ALTER DATABASE [Reservations] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO

ALTER DATABASE [Reservations] SET PARAMETERIZATION SIMPLE 
GO

ALTER DATABASE [Reservations] SET READ_COMMITTED_SNAPSHOT OFF 
GO

ALTER DATABASE [Reservations] SET HONOR_BROKER_PRIORITY OFF 
GO

ALTER DATABASE [Reservations] SET RECOVERY SIMPLE 
GO

ALTER DATABASE [Reservations] SET  MULTI_USER 
GO

ALTER DATABASE [Reservations] SET PAGE_VERIFY CHECKSUM  
GO

ALTER DATABASE [Reservations] SET DB_CHAINING OFF 
GO

ALTER DATABASE [Reservations] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO

ALTER DATABASE [Reservations] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO

ALTER DATABASE [Reservations] SET DELAYED_DURABILITY = DISABLED 
GO

ALTER DATABASE [Reservations] SET ACCELERATED_DATABASE_RECOVERY = OFF  
GO

ALTER DATABASE [Reservations] SET QUERY_STORE = OFF
GO

ALTER DATABASE [Reservations] SET  READ_WRITE 
GO


EXEC sys.sp_dropextendedproperty @name=N'MS_Description' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TableSalles', @level2type=N'COLUMN',@level2name=N'Numero'
GO

/****** Object:  Table [dbo].[TableSalles]    Script Date: 17/12/2023 23:00:31 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TableSalles]') AND type in (N'U'))
DROP TABLE [dbo].[TableSalles]
GO

/****** Object:  Table [dbo].[TableSalles]    Script Date: 17/12/2023 23:00:31 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[TableSalles](
	[Numero] [int] IDENTITY(1,1) NOT NULL,
	[Nom] [nvarchar](50) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[Numero] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Index' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TableSalles', @level2type=N'COLUMN',@level2name=N'Numero'
GO


ALTER TABLE [dbo].[ReservationSalle] DROP CONSTRAINT [FK__Reservati__Salle__37A5467C]
GO

/****** Object:  Table [dbo].[ReservationSalle]    Script Date: 17/12/2023 23:00:18 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[ReservationSalle]') AND type in (N'U'))
DROP TABLE [dbo].[ReservationSalle]
GO

/****** Object:  Table [dbo].[ReservationSalle]    Script Date: 17/12/2023 23:00:18 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[ReservationSalle](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Salle] [int] NOT NULL,
	[AssigneeA] [nvarchar](50) NOT NULL,
	[Date] [nvarchar](15) NOT NULL,
	[Debut] [nvarchar](15) NOT NULL,
	[Fin] [nvarchar](15) NOT NULL,
	[Participants] [int] NOT NULL,
	[Conference] [bit] NOT NULL,
	[Formation] [bit] NOT NULL,
	[Reunion] [bit] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[ReservationSalle]  WITH CHECK ADD FOREIGN KEY([Salle])
REFERENCES [dbo].[TableSalles] ([Numero])
GO


