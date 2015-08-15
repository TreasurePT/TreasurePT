#include "stdafx.h"
#include "armor.h"

#define TOTAL_ARMOR_TYPE 16
#define TOTAL_ARMORS 50
#define MAX_INX_STRING 12

//Respectivamente: DA100 (Nude), DA101 (Battle Suit). [Exceto premiuns.]
char Model[ TOTAL_ARMOR_TYPE ][ TOTAL_ARMORS ][ MAX_INX_STRING ] =
{
	{
		"A001.ini", "A001.ini", "A002.ini", "A003.ini", "A004.ini", "A005.ini", "A006.ini", "A007.ini", "A008.ini",
		"A009.ini", "A010.ini", "A011.ini", "A012.ini", "A013.ini", "A014.ini", "A015.ini", "A016.ini",
		"A017.ini", "A018.ini", "A019.ini", "A020.ini", "A021.ini", "A022.ini", "A023.ini", "A024.ini",
		"A025.ini", "A026.ini", "A027.ini", "A028.ini"
	},
	{
		"Ca001.ini", "Ca002.ini", "Ca003.ini", "Ca004.ini", "Ca005.ini", "Ca006.ini", "Ca007.ini", "Ca008.ini",
		"Ca009.ini", "Ca010.ini", "Ca011.ini", "Ca012.ini", "Ca013.ini", "Ca014.ini", "Ca015.ini", "Ca016.ini",
		"Ca017.ini", "Ca027.ini", "Ca023.ini", "Ca024.ini", "Ca025.ini", "Ca026.ini"
	},
	{
		"B001.ini", "B001.ini", "B002.ini", "B003.ini", "B004.ini", "B005.ini", "B006.ini", "B007.ini", "B008.ini",
		"B009.ini", "B010.ini", "B011.ini", "B012.ini", "B013.ini", "B014.ini", "B015.ini", "B016.ini",
		"B017.ini", "B018.ini", "B019.ini", "B020.ini", "B021.ini", "B022.ini", "B023.ini", "B024.ini",
		"B025.ini", "B026.ini", "B027.ini", "B028.ini"
	},
	{
		"Cb001.ini", "Cb002.ini", "Cb003.ini", "Cb004.ini", "Cb005.ini", "Cb006.ini", "Cb007.ini", "Cb008.ini",
		"Cb009.ini", "Cb010.ini", "Cb011.ini", "Cb012.ini", "Cb013.ini", "Cb014.ini", "Cb015.ini", "Cb016.ini",
		"Cb017.ini", "Cb027.ini", "Cb023.ini", "Cb024.ini", "Cb025.ini", "Cb026.ini"
	},
	{
		"C001.ini", "C001.ini", "C002.ini", "C003.ini", "C004.ini", "C005.ini", "C006.ini", "C007.ini", "C008.ini", "C009.ini",
		"C010.ini", "C011.ini", "C012.ini", "C013.ini", "C014.ini", "C015.ini", "C016.ini", "C017.ini", "C018.ini",
		"C019.ini", "C020.ini", "C021.ini", "C022.ini", "C023.ini", "C024.ini", "C025.ini", "C026.ini", "C027.ini",
		"C028.ini"
	},
	{
		"Cc001.ini", "Cc002.ini", "Cc003.ini", "Cc004.ini", "Cc005.ini", "Cc006.ini", "Cc007.ini", "Cc008.ini",
		"Cc009.ini", "Cc010.ini", "Cc011.ini", "Cc012.ini", "Cc013.ini", "Cc014.ini", "Cc015.ini", "Cc016.ini",
		"Cc017.ini", "Cc027.ini", "Cc023.ini", "Cc024.ini", "Cc025.ini", "Cc026.ini"
	},
	{
		"D001.ini", "D001.ini", "D001.ini", "D002.ini", "D003.ini", "D004.ini", "D005.ini", "D006.ini", "D007.ini", "D008.ini", "D009.ini",
		"D010.ini", "D011.ini", "D012.ini", "D013.ini", "D014.ini", "D015.ini", "D016.ini", "D017.ini", "D018.ini",
		"D019.ini", "D020.ini", "D021.ini", "D022.ini", "D023.ini", "D024.ini", "D025.ini", "D026.ini", "D027.ini",
		"D028.ini"
	},
	{
		"Cd001.ini", "Cd002.ini", "Cd003.ini", "Cd004.ini", "Cd005.ini", "Cd006.ini", "Cd007.ini", "Cd008.ini",
		"Cd009.ini", "Cd010.ini", "Cd011.ini", "Cd012.ini", "Cd013.ini", "Cd014.ini", "Cd015.ini", "Cd016.ini",
		"Cd017.ini", "Cd027.ini", "Cd023.ini", "Cd024.ini", "Cd025.ini", "Cd026.ini"
	},
	{
		"mA001.ini", "mA001.ini", "mA002.ini", "mA003.ini", "mA004.ini", "mA005.ini", "mA006.ini", "mA007.ini", "mA008.ini",
		"mA009.ini", "mA010.ini", "mA011.ini", "mA012.ini", "mA013.ini", "mA014.ini", "mA015.ini", "mA016.ini",
		"mA017.ini", "mA018.ini", "mA019.ini", "mA020.ini", "mA021.ini", "mA022.ini", "mA023.ini", "mA024.ini",
		"mA025.ini", "mA026.ini", "mA027.ini", "mA028.ini"
	},
	{
		"Cma001.ini", "Cma002.ini", "Cma003.ini", "Cma004.ini", "Cma005.ini", "Cma006.ini", "Cma007.ini", "Cma008.ini",
		"Cma009.ini", "Cma010.ini", "Cma011.ini", "Cma012.ini", "Cma013.ini", "Cma014.ini", "Cma015.ini", "Cma016.ini",
		"Cma017.ini", "Cma027.ini", "Cma023.ini", "Cma024.ini", "Cma025.ini", "Cma026.ini"
	},
	{
		"mB001.ini", "mB001.ini", "mB002.ini", "mB003.ini", "mB004.ini", "mB005.ini", "mB006.ini", "mB007.ini", "mB008.ini",
		"mB009.ini", "mB010.ini", "mB011.ini", "mB012.ini", "mB013.ini", "mB014.ini", "mB015.ini", "mB016.ini",
		"mB017.ini", "mB018.ini", "mB019.ini", "mB020.ini", "mB021.ini", "mB022.ini", "mB023.ini", "mB024.ini",
		"mB025.ini", "mB026.ini", "mB027.ini", "mB028.ini"
	},
	{
		"Cmb001.ini", "Cmb002.ini", "Cmb003.ini", "Cmb004.ini", "Cmb005.ini", "Cmb006.ini", "Cmb007.ini", "Cmb008.ini",
		"Cmb009.ini", "Cmb010.ini", "Cmb011.ini", "Cmb012.ini", "Cmb013.ini", "Cmb014.ini", "Cmb015.ini", "Cmb016.ini",
		"Cmb017.ini", "Cmb027.ini", "Cmb023.ini", "Cmb024.ini", "Cmb025.ini", "Cmb026.ini"
	},
	{
		"mC001.ini", "mC001.ini", "mC002.ini", "mC003.ini", "mC004.ini", "mC005.ini", "mC006.ini", "mC007.ini", "mC008.ini",
		"mC009.ini", "mC010.ini", "mC011.ini", "mC012.ini", "mC013.ini", "mC014.ini", "mC015.ini", "mC016.ini",
		"mC017.ini", "mC018.ini", "mC019.ini", "mC020.ini", "mC021.ini", "mC022.ini", "mC023.ini", "mC024.ini",
		"mC025.ini", "mC026.ini", "mC027.ini", "mC028.ini"
	},
	{
		"Cmc001.ini", "Cmc002.ini", "Cmc003.ini", "Cmc004.ini", "Cmc005.ini", "Cmc006.ini", "Cmc007.ini", "Cmc008.ini",
		"Cmc009.ini", "Cmc010.ini", "Cmc011.ini", "Cmc012.ini", "Cmc013.ini", "Cmc014.ini", "Cmc015.ini", "Cmc016.ini",
		"Cmc017.ini", "Cmc027.ini", "Cmc023.ini", "Cmc024.ini", "Cmc025.ini", "Cmc026.ini"
	},
	{
		"mD001.ini", "mD001.ini", "mD002.ini", "mD003.ini", "mD004.ini", "mD005.ini", "mD006.ini", "mD007.ini", "mD008.ini",
		"mD009.ini", "mD010.ini", "mD011.ini", "mD012.ini", "mD013.ini", "mD014.ini", "mD015.ini", "mD016.ini",
		"mD017.ini", "mD018.ini", "mD019.ini", "mD020.ini", "mD021.ini", "mD022.ini", "mD023.ini", "mD024.ini",
		"mD025.ini", "mD026.ini", "mD027.ini", "mD028.ini"
	},
	{
		"Cmd001.ini", "Cmd002.ini", "Cmd003.ini", "Cmd004.ini", "Cmd005.ini", "Cmd006.ini", "Cmd007.ini", "Cmd008.ini",
		"Cmd009.ini", "Cmd010.ini", "Cmd011.ini", "Cmd012.ini", "Cmd013.ini", "Cmd014.ini", "Cmd015.ini", "Cmd016.ini",
		"Cmd017.ini", "Cmd027.ini", "Cmd023.ini", "Cmd024.ini", "Cmd025.ini", "Cmd026.ini"
	}
};

void* Armor_ptr[ ( sizeof( Model ) / 12 ) ] = { 0 };

void Armor::SetNewArmors( )
{
	for( int i = 0; i < TOTAL_ARMOR_TYPE; i++ )
	{
		for( int c = 0; c < TOTAL_ARMORS; c++ )
		{
			Armor_ptr[ i * TOTAL_ARMORS + c ] = &Model[ i ][ c ];
		};
	};

	WriteMemory( 0x004596B5 + 1, ( int )&Armor_ptr[ 0 ] );
	WriteMemory( 0x00459A8B + 3, ( int )&Armor_ptr[ 0 ] );
	WriteMemory( 0x00459C77 + 3, ( int )&Armor_ptr[ 0 ] );
	WriteMemory( 0x00459E1C + 3, ( int )&Armor_ptr[ 0 ] );
	WriteMemory( 0x0045A22C + 3, ( int )&Armor_ptr[ 0 ] );
	WriteMemory( 0x0045A300 + 3, ( int )&Armor_ptr[ 0 ] );
	WriteMemory( 0x004596F8 + 2, ( int )&Armor_ptr[ ( sizeof( Model ) / 12 ) - 1 ] );
};

void __cdecl Initialize_New_Armors( )
{
	std::shared_ptr<Armor> lpArmor = std::make_shared<Armor>( );
	lpArmor->SetNewArmors( );
};