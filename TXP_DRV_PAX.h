/****************************************************************************

	Thorlabs TXP_DRV_PAX - PAX57xx polarization analyzer instrument driver

	Copyright:	Copyright(c) 2005, Thorlabs GmbH (www.thorlabs.com)
	Author:		Michael Biebl (mbiebl@thorlabs.com)
	            Lutz Hoerl (lhoerl@thorlabs.com)

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA


	Header file

	Date:					Apr-21-2005
	Software-Nr:		09.156.xxx
	Version:				1.0

	Changelog:			see 'TXP_DRV_PAX.c'

****************************************************************************/

#ifndef __TXPPAX_HEADER
#define __TXPPAX_HEADER

#include "vpptype.h"
//#include <cvidef.h>

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C"
{
#endif


/*=============================================================================
 Macros
=============================================================================*/
#define TXPPAX_MODULE_NUMBER					0x70	// this is the TXP system's module number for PAX modules
#define TXPPAX_MAX_SLOT_COUNT					64		// max. number of slots in a TXP chassis


/*---------------------------------------------------------------------------
 Range checking values
---------------------------------------------------------------------------*/
#define TXPPAX_POWER_OVERFLOW_VAL			1.0E7

#define TXPPAX_MIN_DOP_VAL						0.0
#define TXPPAX_MAX_DOP_VAL						200.0

#define TXPPAX_MIN_AZIMUTH_VAL				-90.0
#define TXPPAX_MAX_AZIMUTH_VAL				90.0

#define TXPPAX_MIN_ELLIPTICITY_VAL			-45.0
#define TXPPAX_MAX_ELLIPTICITY_VAL			45.0

#define TXPPAX_MIN_STOKES_VAL					-1.0
#define TXPPAX_MAX_STOKES_VAL					1.0


/*---------------------------------------------------------------------------
 Buffers
---------------------------------------------------------------------------*/
#define TXPPAX_BUFFER_SIZE						512	// General buffer size
#define TXPPAX_ERR_DESCR_BUFFER_SIZE		256	// Buffer size for error messages
#define TXPPAX_ID_STRING_BUFFER_SIZE		65		// Buffer size for ID string purposes


/*---------------------------------------------------------------------------
 Error/Warning Codes
---------------------------------------------------------------------------*/
// Offsets
#define VI_DRIVER_ERROR_OFFSET				(_VI_ERROR 					 + 0x3FFC0800L)	// 0xBFFC0800
#define VI_TXP_RM_ERROR_OFFSET				(VI_DRIVER_ERROR_OFFSET  +     0x0100L)	// 0xBFFC0900
#define VI_TXP_MOD_ERROR_OFFSET				(VI_TXP_RM_ERROR_OFFSET  +     0x0100L)	// 0xBFFC0A00
#define VI_TXP_PAX_ERROR_OFFSET				(VI_TXP_MOD_ERROR_OFFSET +     0x0100L)	// 0xBFFC0B00

// Driver error codes
#define VI_ERROR_TRANSMIT_INCOMPLETE		(VI_DRIVER_ERROR_OFFSET + 0x07L)		// 0xBFFC0807
#define VI_ERROR_CARD_BOOT_TIMEOUT			(VI_DRIVER_ERROR_OFFSET + 0x08L)		// 0xBFFC0808
#define VI_ERROR_TIME_CONVERSION				(VI_DRIVER_ERROR_OFFSET + 0x09L)		// 0xBFFC0809
#define VI_ERROR_PARAMETER9					(VI_DRIVER_ERROR_OFFSET + 0x0AL)		// 0xBFFC080A
#define VI_ERROR_PARAMETER10					(VI_DRIVER_ERROR_OFFSET + 0x0BL)		// 0xBFFC080B
#define VI_ERROR_PARAMETER11					(VI_DRIVER_ERROR_OFFSET + 0x0CL)		// 0xBFFC080C
#define VI_ERROR_PARAMETER12					(VI_DRIVER_ERROR_OFFSET + 0x0DL)		// 0xBFFC080D
#define VI_ERROR_PARAMETER13					(VI_DRIVER_ERROR_OFFSET + 0x0EL)		// 0xBFFC080E
#define VI_ERROR_PARAMETER14					(VI_DRIVER_ERROR_OFFSET + 0x0FL)		// 0xBFFC080F
#define VI_ERROR_PARAMETER15					(VI_DRIVER_ERROR_OFFSET + 0x10L)		// 0xBFFC0810
#define VI_ERROR_PARAMETER16					(VI_DRIVER_ERROR_OFFSET + 0x11L)		// 0xBFFC0811

// Static TXP Resource Manager error codes
#define VI_ERROR_TXP_RM_SUCCESS				(VI_TXP_RM_ERROR_OFFSET + 0x00L)  	// (0xBFFC0900) Success.
#define VI_ERROR_TXP_RM_KEY					(VI_TXP_RM_ERROR_OFFSET + 0x01L)  	// (0xBFFC0901) Wrong key while attempt to set a new access code.
#define VI_ERROR_TXP_RM_RANGE					(VI_TXP_RM_ERROR_OFFSET + 0x02L)  	// (0xBFFC0902) A given set value was too big or too small.
#define VI_ERROR_TXP_RM_PERM					(VI_TXP_RM_ERROR_OFFSET + 0x03L)  	// (0xBFFC0903) The users access level does not allow this command.
#define VI_ERROR_TXP_RM_UNKNOWN				(VI_TXP_RM_ERROR_OFFSET + 0x04L)  	// (0xBFFC0904) No error description available.
#define VI_ERROR_TXP_RM_TXTOVFL				(VI_TXP_RM_ERROR_OFFSET + 0x05L)  	// (0xBFFC0905) Text size is too big for target destination.
#define VI_ERROR_TXP_RM_TIME					(VI_TXP_RM_ERROR_OFFSET + 0x06L)  	// (0xBFFC0906) The given time was out of the valid range.
#define VI_ERROR_TXP_RM_KEY_EXPIRED			(VI_TXP_RM_ERROR_OFFSET + 0x07L)  	// (0xBFFC0907) The access key given has expired.
#define VI_ERROR_TXP_RM_NOT_IMPLEMENTED	(VI_TXP_RM_ERROR_OFFSET + 0x08L)  	// (0xBFFC0908) Command is not implemented yet.
#define VI_ERROR_TXP_RM_PARSER_PARAM		(VI_TXP_RM_ERROR_OFFSET + 0x09L)  	// (0xBFFC0909) The number of given parameters was wrong.
#define VI_ERROR_TXP_RM_WRONG_CARD			(VI_TXP_RM_ERROR_OFFSET + 0x10L)  	// (0xBFFC0910) No card available at given slot/at given module.
#define VI_ERROR_TXP_RM_WRONG_MODULE		(VI_TXP_RM_ERROR_OFFSET + 0x11L)  	// (0xBFFC0911) The given module name is unknown.
#define VI_ERROR_TXP_RM_CARD_NOT_READY		(VI_TXP_RM_ERROR_OFFSET + 0x12L)  	// (0xBFFC0912) Command cannot be executed because - card not ready.
#define VI_ERROR_TXP_RM_CARD_ERROR			(VI_TXP_RM_ERROR_OFFSET + 0x13L)  	// (0xBFFC0913) Card returns erroneous data.
#define VI_ERROR_TXP_RM_DEVICE_NOT_FOUND	(VI_TXP_RM_ERROR_OFFSET + 0x14L)  	// (0xBFFC0914) Card device name not found in ini-file.
#define VI_ERROR_TXP_RM_MALLOC				(VI_TXP_RM_ERROR_OFFSET + 0x15L)  	// (0xBFFC0915) The system ran out of memory.
#define VI_ERROR_TXP_RM_FATAL					(VI_TXP_RM_ERROR_OFFSET + 0x16L)  	// (0xBFFC0916) Unrecoverable system error.
#define VI_ERROR_TXP_RM_NO_STD_MODULE		(VI_TXP_RM_ERROR_OFFSET + 0x17L)  	// (0xBFFC0917) No module installed for this card type.
#define VI_ERROR_TXP_RM_SLOT_BUSY			(VI_TXP_RM_ERROR_OFFSET + 0x18L)  	// (0xBFFC0918) Requested slot is already busy with another module.
#define VI_ERROR_TXP_RM_RANGE_WARNING		(VI_TXP_RM_ERROR_OFFSET + 0x19L)  	// (0xBFFC0919) The measurement value is out of the display range.
#define VI_ERROR_TXP_RM_CMD_NOT_FOUND		(VI_TXP_RM_ERROR_OFFSET + 0x20L)  	// (0xBFFC0920) Command was not found in the list of valid commands.
#define VI_ERROR_TXP_RM_ZOMBIE				(VI_TXP_RM_ERROR_OFFSET + 0x21L)  	// (0xBFFC0921) Unrecoverable module error.
#define VI_ERROR_TXP_RM_WRONG_TYPE			(VI_TXP_RM_ERROR_OFFSET + 0x30L)  	// (0xBFFC0930) The command given is not valid for the used card.
#define VI_ERROR_TXP_RM_ADJUST				(VI_TXP_RM_ERROR_OFFSET + 0x31L)  	// (0xBFFC0931) An error occured due to missing adjustment data.
#define VI_ERROR_TXP_RM_SERVICE				(VI_TXP_RM_ERROR_OFFSET + 0x32L)  	// (0xBFFC0932) Wrong service configuration for the command.
#define VI_ERROR_TXP_RM_OTP					(VI_TXP_RM_ERROR_OFFSET + 0x33L)  	// (0xBFFC0933) The card's temperature is too high.
#define VI_ERROR_TXP_RM_ALARM					(VI_TXP_RM_ERROR_OFFSET + 0x34L)  	// (0xBFFC0934) Chassis alarm.
#define VI_ERROR_TXP_RM_OPTION				(VI_TXP_RM_ERROR_OFFSET + 0x35L)  	// (0xBFFC0935) Option conflict.
#define VI_ERROR_TXP_RM_MATH					(VI_TXP_RM_ERROR_OFFSET + 0x40L)  	// (0xBFFC0940) An internal calculation failed.
#define VI_ERROR_TXP_RM_MATH_FAULT			(VI_TXP_RM_ERROR_OFFSET + 0x41L)  	// (0xBFFC0941) A call to a library returned with error EFAULT.
#define VI_ERROR_TXP_RM_MATH_INVAL			(VI_TXP_RM_ERROR_OFFSET + 0x42L)  	// (0xBFFC0942) A call to a library returned with error EINVAL.
#define VI_ERROR_TXP_RM_MATH_DOM				(VI_TXP_RM_ERROR_OFFSET + 0x43L)	 	// (0xBFFC0943) A call to a library returned with error EDOM


// Static common TXP Module error codes
#define VI_ERROR_TXP_MOD_SUCCESS				(VI_TXP_MOD_ERROR_OFFSET + 0x00L)	// (0xBFFC0A00) no error
#define VI_ERROR_TXP_MOD_REBOOT				(VI_TXP_MOD_ERROR_OFFSET + 0x01L)	// (0xBFFC0A01) reboot required
#define VI_ERROR_TXP_MOD_IO					(VI_TXP_MOD_ERROR_OFFSET + 0x02L)	// (0xBFFC0A02) hardware error
#define VI_ERROR_TXP_MOD_FAULT				(VI_TXP_MOD_ERROR_OFFSET + 0x03L)  	// (0xBFFC0A03) miscelaneous error
#define VI_ERROR_TXP_MOD_TYPE					(VI_TXP_MOD_ERROR_OFFSET + 0x04L)  	// (0xBFFC0A04) card type mismatch
#define VI_ERROR_TXP_MOD_UNKNOWN				(VI_TXP_MOD_ERROR_OFFSET + 0x05L)  	// (0xBFFC0A05) unknown command
#define VI_ERROR_TXP_MOD_PARAMETER			(VI_TXP_MOD_ERROR_OFFSET + 0x06L)  	// (0xBFFC0A06) wrong number or type of command parameters
#define VI_ERROR_TXP_MOD_RANGE				(VI_TXP_MOD_ERROR_OFFSET + 0x07L)  	// (0xBFFC0A07) out of range
#define VI_ERROR_TXP_MOD_CHECKSUM			(VI_TXP_MOD_ERROR_OFFSET + 0x08L)  	// (0xBFFC0A08) EEPROM checksum error
#define VI_ERROR_TXP_MOD_TEMP					(VI_TXP_MOD_ERROR_OFFSET + 0x09L)  	// (0xBFFC0A09) no temperature sensor to check the cooler temperature
#define VI_ERROR_TXP_MOD_ALARM				(VI_TXP_MOD_ERROR_OFFSET + 0x0AL)  	// (0xBFFC0A0A) chassis ALARM signal detected
#define VI_ERROR_TXP_MOD_INTERLK				(VI_TXP_MOD_ERROR_OFFSET + 0x0BL)  	// (0xBFFC0A0B) Interlock open signal detected
#define VI_ERROR_TXP_MOD_OTP					(VI_TXP_MOD_ERROR_OFFSET + 0x0CL)  	// (0xBFFC0A0C) over temperature signal detected
#define VI_ERROR_TXP_MOD_SHUTTER				(VI_TXP_MOD_ERROR_OFFSET + 0x0DL)  	// (0xBFFC0A0D) shutter failure signal detected
#define VI_ERROR_TXP_MOD_SUPPLY				(VI_TXP_MOD_ERROR_OFFSET + 0x0EL)  	// (0xBFFC0A0E) power supply error detected
#define VI_ERROR_TXP_MOD_LIMIT				(VI_TXP_MOD_ERROR_OFFSET + 0x0FL)  	// (0xBFFC0A0F) current limit reached
#define VI_ERROR_TXP_MOD_TFAIL				(VI_TXP_MOD_ERROR_OFFSET + 0x10L)  	// (0xBFFC0A10) temperature window error
#define VI_ERROR_TXP_MOD_SENSOR				(VI_TXP_MOD_ERROR_OFFSET + 0x11L)  	// (0xBFFC0A11) no sensor detected
#define VI_ERROR_TXP_MOD_LDOPEN				(VI_TXP_MOD_ERROR_OFFSET + 0x12L)  	// (0xBFFC0A12) LD open circiut
#define VI_ERROR_TXP_MOD_TECOPEN				(VI_TXP_MOD_ERROR_OFFSET + 0x13L)  	// (0xBFFC0A13) TEC open circiut
#define VI_ERROR_TXP_MOD_LDC					(VI_TXP_MOD_ERROR_OFFSET + 0x14L)  	// (0xBFFC0A14) the LD output is on
#define VI_ERROR_TXP_MOD_TEC					(VI_TXP_MOD_ERROR_OFFSET + 0x15L)  	// (0xBFFC0A15) the TEC output is on
#define VI_ERROR_TXP_MOD_BIAS					(VI_TXP_MOD_ERROR_OFFSET + 0x16L)  	// (0xBFFC0A16) the BIAS is on
#define VI_ERROR_TXP_MOD_MODECC				(VI_TXP_MOD_ERROR_OFFSET + 0x17L)  	// (0xBFFC0A17) not possible in constant current mode
#define VI_ERROR_TXP_MOD_MODECP				(VI_TXP_MOD_ERROR_OFFSET + 0x18L)  	// (0xBFFC0A18) not possible in constant power mode
#define VI_ERROR_TXP_MOD_SEQUENCE			(VI_TXP_MOD_ERROR_OFFSET + 0x19L)  	// (0xBFFC0A19) command sequence violation
#define VI_ERROR_TXP_MOD_MACRO				(VI_TXP_MOD_ERROR_OFFSET + 0x1AL)  	// (0xBFFC0A1A) not possible while macro running
#define VI_ERROR_TXP_MOD_BUF_END				(VI_TXP_MOD_ERROR_OFFSET + 0x1BL)  	// (0xBFFC0A1B) end of buffer
#define VI_ERROR_TXP_MOD_OPMODE				(VI_TXP_MOD_ERROR_OFFSET + 0x1CL)  	// (0xBFFC0A1C) wrong operating mode
#define VI_ERROR_TXP_MOD_ADJUST				(VI_TXP_MOD_ERROR_OFFSET + 0x1DL)  	// (0xBFFC0A1D) adjustment error
#define VI_ERROR_TXP_MOD_BUSY					(VI_TXP_MOD_ERROR_OFFSET + 0x1EL)  	// (0xBFFC0A1E) card is busy(try again later)
#define VI_ERROR_TXP_MOD_MEMORY				(VI_TXP_MOD_ERROR_OFFSET + 0x1FL)  	// (0xBFFC0A1F) card memory error
#define VI_ERROR_TXP_MOD_INPUT_VAL			(VI_TXP_MOD_ERROR_OFFSET + 0x20L)  	// (0xBFFC0A20) Input/measurement value out of range
#define VI_ERROR_TXP_MOD_OVERFLOW			(VI_TXP_MOD_ERROR_OFFSET + 0x21L)  	// (0xBFFC0A21) Input/measurement value overflow
#define VI_ERROR_TXP_MOD_MODULATION			(VI_TXP_MOD_ERROR_OFFSET + 0x22L)  	// (0xBFFC0A22) switching of modulation mode impossible
#define VI_ERROR_TXP_MOD_TRIGGER				(VI_TXP_MOD_ERROR_OFFSET + 0x23L)  	// (0xBFFC0A23) Trigger error; Wrong trigger source or trigger not ready.
#define VI_ERROR_TXP_MOD_SERVICE				(VI_TXP_MOD_ERROR_OFFSET + 0x24L)  	// (0xBFFC0A24) Wrong service configuration; The actual service configuration does not allow the command given.
#define VI_ERROR_TXP_MOD_OPTION				(VI_TXP_MOD_ERROR_OFFSET + 0x25L)  	// (0xBFFC0A25) Command not supported because of missing options


// Static TXP PAX module error codes
// - none -


/*---------------------------------------------------------------------------
 Status reporting
---------------------------------------------------------------------------*/
#define TXPPAX_STATBIT_CARD_EVENT		0x00000001L		// Card event 
#define TXPPAX_STATBIT_OVERTEMP 			0x00000002L		// Overtemperature
#define TXPPAX_STATBIT_COOLING  			0x00000004L		// Cooling requirement (reserved)
#define TXPPAX_STATBIT_VCC_FAIL      	0x00000008L		// Power supply error
#define TXPPAX_STATBIT_ALARM    			0x00000010L		// Chassis alarm
#define TXPPAX_STATBIT_CARD_PRESENT  	0x00000020L		// Card present (reserved)
#define TXPPAX_STATBIT_CARD_READY    	0x00000040L		// Card ready (reserved)
#define TXPPAX_STATBIT_GPIO     			0x00000080L		// General Purpose I/O (reserved)
#define TXPPAX_STATBIT_SENSOR_MISSING	0x00000100L		//	Sensor head missing
#define TXPPAX_STATBIT_MACRO_ACTIVE		0x00000200L		//	Macro active
#define TXPPAX_STATBIT_TRIGGER_WAIT		0x00000400L		//	Waiting for trigger signal
#define TXPPAX_STATBIT_POWER_RANGE		0x00000800L		//	Optical power too high
#define TXPPAX_STATBIT_SENSOR_TEMP		0x00001000L		//	Sensor temperature out of range
#define TXPPAX_STATBIT_SPEED				0x00002000L		//	Sensor revolution speed out of range
#define TXPPAX_STATBIT_SENSOR_ADJ		0x00004000L		//	Sensor adjustment data invalid
#define TXPPAX_STATBIT_CARD_ADJ			0x00008000L		//	Card adjustment data invalid


/*---------------------------------------------------------------------------
 Access key control bitmaps
---------------------------------------------------------------------------*/
#define TXPPAX_ACCKEY_SERNR				0x00000001L		//	change card serial number (reserved, internal use)
#define TXPPAX_ACCKEY_BLD_DATE			0x00000002L		//	change build date (reserved, internal use)
#define TXPPAX_ACCKEY_REP_DATE			0x00000004L		//	change repair date (reserved, internal use)
#define TXPPAX_ACCKEY_ADJ_DATE			0x00000008L		//	change adjustment date (reserved, internal use)
#define TXPPAX_ACCKEY_CAL_DATE			0x00000010L		//	change calibration date (reserved, internal use)
#define TXPPAX_ACCKEY_USER_TXT			0x00000020L		//	change card user text
#define TXPPAX_ACCKEY_SERVICE				0x00000100L		//	Permits service functions (reserved, internal use) 
#define TXPPAX_ACCKEY_STATE				0x00000200L		//	Permits switching on/off outputs and functions or changing configurations.
#define TXPPAX_ACCKEY_SETVAL				0x00000400L		//	Permits setting set values

#define TXPPAX_ACCKEY_ADJUST				TXPPAX_ACCKEY_ADJ_DATE	//	Permits writing adjustment data (reserved, internal use)


/*---------------------------------------------------------------------------
 Operating modes (see function 'TXPPAX_SetOperatingMode()')
---------------------------------------------------------------------------*/
#define TXPPAX_OPMODE_STANDBY 			0x00
#define TXPPAX_OPMODE_SINGLE_MEAS 		0x01
#define TXPPAX_OPMODE_ARRAY_MEAS 		0x02
#define TXPPAX_OPMODE_CAB_MEAS 			0x10		// for service purposes only
#define TXPPAX_OPMODE_FFT_SINGLE_MEAS  0x11		// for service purposes only
#define TXPPAX_OPMODE_FFT_ARRAY_MEAS   0x12		// for service purposes only


/*---------------------------------------------------------------------------
 Input Power ranges (see function 'TXPPAX_SetPowerRange()')
---------------------------------------------------------------------------*/
#define TXPPAX_RANGE_AUTO 					0
#define TXPPAX_RANGE_1 						1 	// highest
#define TXPPAX_RANGE_2 						2
#define TXPPAX_RANGE_3 						3
#define TXPPAX_RANGE_4 						4
#define TXPPAX_RANGE_5 						5
#define TXPPAX_RANGE_6 						6
#define TXPPAX_RANGE_7 						7
#define TXPPAX_RANGE_8 						8


/*---------------------------------------------------------------------------
 Array trigger modes
---------------------------------------------------------------------------*/
#define TXPPAX_TRIGGER_OFF 				0	// immediate trigger - parameter 'pre_trigger' is ignored
#define TXPPAX_TRIGGER_SOFTWARE			1 	// Software trigger 
#define TXPPAX_TRIGGER_FALLING 			2  // Hardware trigger - falling edge
#define TXPPAX_TRIGGER_RISING 			3  // Hardware trigger - rising edge


/*---------------------------------------------------------------------------
 Supported card types
---------------------------------------------------------------------------*/
#define TXPPAX_CARD_TYPE_PAX				0x70L				// standard PAX card type number


/*---------------------------------------------------------------------------
 Card software/hardware options, assembly variants
---------------------------------------------------------------------------*/
// Software options
#define TXPPAX_SW_OPT_SKIP_DSP_RUNNING	0x01L				// skip checking for DSP running

// Assembly variants
#define TXPPAX_ASSY_INTERNAL_SENSOR		0x01L				// card with built-in optical sensor


/*---------------------------------------------------------------------------
 Sensor type number and option bitmaps
---------------------------------------------------------------------------*/
#define TXPPAX_SENSOR_OPT_SUTTER			0x80000000L		// optical sensor has a shutter option


/*---------------------------------------------------------------------------
 Selftest results
---------------------------------------------------------------------------*/
#define TXPPAX_SELFTEST_SUCCESS			0


/*---------------------------------------------------------------------------
 Adjustment objects
---------------------------------------------------------------------------*/
#define TXPPAX_ADJOBJ_DAC_2P 				0
#define TXPPAX_ADJOBJ_DAC_MP 				1
#define TXPPAX_ADJOBJ_ADC_2P 				2
#define TXPPAX_ADJOBJ_ADC_MP 				3

#define TXPPAX_ADJ_INVALID    			0
#define TXPPAX_ADJ_VALID      			1
#define TXPPAX_ADJ_DO_NOT_USE 			2


/*---------------------------------------------------------------------------
 Card's general purpose memory specifier (service only)
---------------------------------------------------------------------------*/
#define TXPPAX_CARD_GPVALMEM_RAM    	0
#define TXPPAX_CARD_GPVALMEM_EEPROM_A  1
#define TXPPAX_CARD_GPVALMEM_EEPROM_B  2



/*=============================================================================
 GLOBAL USER-CALLABLE FUNCTION DECLARATIONS (Exportable Functions)
=============================================================================*/

// Init / close
ViStatus _VI_FUNC TXPPAX_init (ViRsrc resourceName, ViUInt32 slot, ViString userId, ViUInt32 commTmo, ViUInt32 bootTmo, ViUInt32 keepAliveTime, ViPSession instrHandle);
ViStatus _VI_FUNC TXPPAX_close (ViSession instrument);


// Configure
ViStatus _VI_FUNC TXPPAX_SetWavelength (ViSession instr, ViReal64 wavelength);
ViStatus _VI_FUNC TXPPAX_GetWavelength (ViSession instr, ViPReal64 wavelength);
ViStatus _VI_FUNC TXPPAX_GetWavelengthRange (ViSession instr, ViPReal64 min, ViPReal64 max, ViPReal64 def);

ViStatus _VI_FUNC TXPPAX_SetPowerRange (ViSession instr, ViUInt8 powerRange);
ViStatus _VI_FUNC TXPPAX_GetPowerRange (ViSession instr, ViPUInt8 setPowerRange, ViPUInt8 currentPowerRange);
ViStatus _VI_FUNC TXPPAX_GetMaxPowerRange (ViSession instr, ViPUInt8 maxRange);
ViStatus _VI_FUNC TXPPAX_GetPowerRangeValues (ViSession instr, ViUInt8 powerRange, ViPReal64 min, ViPReal64 max);

ViStatus _VI_FUNC TXPPAX_SetBasicMeasSpeed (ViSession instr, ViReal64 speed);
ViStatus _VI_FUNC TXPPAX_GetBasicMeasSpeed (ViSession instr, ViPReal64 speed);
ViStatus _VI_FUNC TXPPAX_GetBasicMeasSpeedRange (ViSession instr, ViPReal64 minSpeed, ViPReal64 maxSpeed, ViPReal64 defSpeed);

ViStatus _VI_FUNC TXPPAX_SetShutterAttenuation (ViSession instr, ViReal64 att);
ViStatus _VI_FUNC TXPPAX_GetShutterAttenuation (ViSession instr, ViPReal64 att);
ViStatus _VI_FUNC TXPPAX_GetShutterAttenuationRange (ViSession instr, ViPReal64 minAtt, ViPReal64 maxAtt, ViPReal64 defAtt);


// Action / Status
ViStatus _VI_FUNC TXPPAX_GetStatus (ViSession instrumentHandle, ViPUInt32 eventRegister, ViPUInt32 statusRegister);

ViStatus _VI_FUNC TXPPAX_SetOperatingMode (ViSession instr, ViUInt8 opMode);
ViStatus _VI_FUNC TXPPAX_GetOperatingMode (ViSession instr, ViPUInt8 opMode);


// Data - Single Measurement
ViStatus _VI_FUNC TXPPAX_RestartSingleMeas (ViSession instr);
ViStatus _VI_FUNC TXPPAX_GetSingleMeas (ViSession instr, ViBoolean block, ViPReal64 stokes1, ViPReal64 stokes2, ViPReal64 stokes3, ViPReal64 azimuth, ViPReal64 ellipticity, ViPReal64 dop, ViPReal64 power, ViPUInt32 newMeas);
ViStatus _VI_FUNC TXPPAX_SetSingleMeasParameters (ViSession instr, ViUInt32 numPeriod, ViUInt32 numBuf, ViUInt32 numFFT);
ViStatus _VI_FUNC TXPPAX_GetSingleMeasParameters (ViSession instr, ViPUInt32 numPeriod, ViPUInt32 numBuf, ViPUInt32 numFFT);
ViStatus _VI_FUNC TXPPAX_GetSingleMeasParametersRange (ViSession instr, ViPUInt32 minNumPeriod, ViPUInt32 maxNumPeriod, ViPUInt32 defNumPeriod,
                                                       						ViPUInt32 minNumBuf,    ViPUInt32 maxNumBuf,    ViPUInt32 defNumBuf,
                                                       						ViPUInt32 minNumFFT,    ViPUInt32 maxNumFFT,    ViPUInt32 defNumFFT);


// Data - Array Measurement
ViStatus _VI_FUNC TXPPAX_GetArrayMeas (ViSession instr, ViReal64 _VI_FAR stokes1[], ViReal64 _VI_FAR stokes2[], ViReal64 _VI_FAR stokes3[],
                                       					  ViReal64 _VI_FAR azimuth[], ViReal64 _VI_FAR ellipticity[], ViReal64 _VI_FAR dop[], ViReal64 _VI_FAR power[], 
                                                        ViUInt32 arraySize, ViPUInt32 retCount);
ViStatus _VI_FUNC TXPPAX_StartArrayMeas (ViSession instr);
ViStatus _VI_FUNC TXPPAX_TriggerArrayMeas (ViSession instr);
ViStatus _VI_FUNC TXPPAX_SetArrayMeasParameters (ViSession instr, ViUInt32 numPer, ViUInt32 numBuf, ViUInt32 numFFT, ViUInt32 numMeas, ViUInt32 recRate, ViUInt32 preTrg, ViUInt8 trgSrc);
ViStatus _VI_FUNC TXPPAX_GetArrayMeasParameters (ViSession instr, ViPUInt32 numPer, ViPUInt32 numBuf, ViPUInt32 numFFT, ViPUInt32 numMeas, ViPUInt32 recRate, ViPUInt32 preTrg, ViPUInt8 trgSrc);
ViStatus _VI_FUNC TXPPAX_GetArrayMeasParametersRange (ViSession instr, ViPUInt32 minPer, ViPUInt32 maxPer, ViPUInt32 defPer, ViPUInt32 minBuf, ViPUInt32 maxBuf, ViPUInt32 defBuf, ViPUInt32 minFFT, ViPUInt32 maxFFT, ViPUInt32 defFFT); 
ViStatus _VI_FUNC TXPPAX_GetArrayRecordParametersRange (ViSession instr, ViPUInt32 minMeas, ViPUInt32 maxMeas, ViPUInt32 defMeas, ViPUInt32 minRate, ViPUInt32 maxRate, ViPUInt32 defRate, ViPUInt32 minTrg, ViPUInt32 maxTrg, ViPUInt32 defTrg, ViPUInt8 defTrgSrc);


// Utility
ViStatus _VI_FUNC TXPPAX_errorMessage (ViSession instr, ViStatus status, ViChar _VI_FAR message[]);
ViStatus _VI_FUNC TXPPAX_IdentifyCard (ViSession instr, ViBoolean enable);


// Utility - Connection Setup
ViStatus _VI_FUNC TXPPAX_GetKeepAliveTime (ViSession instr, ViPUInt32 keepAliveTime);
ViStatus _VI_FUNC TXPPAX_SetKeepAliveTime (ViSession instr, ViUInt32 keepAliveTime);
ViStatus _VI_FUNC TXPPAX_SendKeepAlivePacket (ViSession instr);


// Utility - Access Key
ViStatus _VI_FUNC TXPPAX_GetAccessLevel (ViSession instr, ViPUInt32 effecticeAccessKey, ViPUInt32 maximumAccessKey);
ViStatus _VI_FUNC TXPPAX_SetAccessLevel (ViSession instr, ViUInt32 effectiveAccessKey);
ViStatus _VI_FUNC TXPPAX_SetKeyData (ViSession instr);


// Utility - Information
ViStatus _VI_FUNC TXPPAX_SetCardUserText (ViSession instr, ViChar _VI_FAR userText[]);
ViStatus _VI_FUNC TXPPAX_GetCardUserText (ViSession instr, ViChar _VI_FAR userText[]);
ViStatus _VI_FUNC TXPPAX_GetDriverInfo (ViSession instr, ViChar _VI_FAR driverName[], ViPUInt32 Version);
ViStatus _VI_FUNC TXPPAX_GetModuleInfo (ViSession instr, ViChar _VI_FAR moduleName[], ViPUInt32 Version, ViChar _VI_FARuserId[]);
ViStatus _VI_FUNC TXPPAX_GetCardInfo (ViSession instr, ViPUInt32 type, ViPUInt32 swOpt, ViPUInt32 hwOpt, ViPUInt32 assy, ViPReal64 power, ViChar _VI_FAR name[], ViChar _VI_FAR serNr[], ViChar _VI_FAR fwName[], ViPUInt32 uCVer, ViPUInt32 DSPVer);
ViStatus _VI_FUNC TXPPAX_GetCardDateInfo (ViSession instr, ViPUInt32 assyDate, ViPUInt32 repDate, ViPUInt32 adjDate, ViPUInt32 calDate, ViPUInt32 nextDate);
ViStatus _VI_FUNC TXPPAX_GetCardBootTime (ViSession instr, ViPUInt32 bootTime);
ViStatus _VI_FUNC TXPPAX_GetCardTemp (ViSession instr, ViPReal64 temp);
ViStatus _VI_FUNC TXPPAX_GetSensorInfo (ViSession instr, ViPUInt32 type, ViChar _VI_FAR name[], ViChar _VI_FAR serNr[]);
ViStatus _VI_FUNC TXPPAX_GetSensorDateInfo (ViSession instr, ViPUInt32 assyDate, ViPUInt32 repDate, ViPUInt32 adjDate, ViPUInt32 calDate, ViPUInt32 nextDate);
ViStatus _VI_FUNC TXPPAX_GetSensorTemp (ViSession instr, ViPReal64 temp);


// Utility - Time/Date conversion
ViStatus _VI_FUNC TXPPAX_ConvTxpToWinTime (ViSession instr, ViUInt32 TXPTime, ViPUInt32 windowsTime);
ViStatus _VI_FUNC TXPPAX_ConvWinToTxpTime (ViSession instr, ViUInt32 windowsTime, ViPUInt32 TXPTime);
ViStatus _VI_FUNC TXPPAX_ConvWinToMDY (ViSession instr, ViUInt32 time, ViPInt32 month, ViPInt32 day, ViPInt32 year, ViPInt32 hour, ViPInt32 minute, ViPInt32 second);


// Utility - Service - Debug
ViStatus _VI_FUNC TXPPAX_EnableDebug (ViSession instrumentHandle, ViBoolean debugOutput);


// Utility - Service - Card Setup
ViStatus _VI_FUNC TXPPAX_SetCardName (ViSession instr, ViChar _VI_FAR name[]);
ViStatus _VI_FUNC TXPPAX_SetCardSerNr (ViSession instr, ViChar _VI_FAR serNr[]);
ViStatus _VI_FUNC TXPPAX_SetCardAssyDate (ViSession instr, ViUInt32 assy);
ViStatus _VI_FUNC TXPPAX_SetCardRepDate (ViSession instr, ViUInt32 rep);
ViStatus _VI_FUNC TXPPAX_SetCardAdjDate (ViSession instr, ViUInt32 adj);
ViStatus _VI_FUNC TXPPAX_SetCardCalDate (ViSession instr, ViUInt32 cal, ViUInt32 next);
ViStatus _VI_FUNC TXPPAX_SetCardOptions (ViSession instr, ViUInt32 swOpt, ViUInt32 hwOpt, ViUInt32 assy, ViReal64 pow);
ViStatus _VI_FUNC TXPPAX_SetCardGPValues (ViSession instr, ViUInt8 mem, ViInt32 _VI_FAR values[]);
ViStatus _VI_FUNC TXPPAX_GetCardGPValues (ViSession instr, ViUInt8 mem, ViInt32 _VI_FAR values[]);


// Utility - Service - Sensor Setup
ViStatus _VI_FUNC TXPPAX_SetSensorEepromMapping (ViSession instr, ViUInt32 mapping);
ViStatus _VI_FUNC TXPPAX_GetSensorEepromMapping (ViSession instr, ViPUInt32 mapping);
ViStatus _VI_FUNC TXPPAX_SetSensorType (ViSession instr, ViUInt32 type);
ViStatus _VI_FUNC TXPPAX_SetSensorName (ViSession instr, ViChar _VI_FAR name[]);
ViStatus _VI_FUNC TXPPAX_SetSensorSerNr (ViSession instr, ViChar _VI_FAR serNr[]);
ViStatus _VI_FUNC TXPPAX_SetSensorAssyDate (ViSession instr, ViUInt32 assy);
ViStatus _VI_FUNC TXPPAX_SetSensorRepDate (ViSession instr, ViUInt32 rep);
ViStatus _VI_FUNC TXPPAX_SetSensorAdjDate (ViSession instr, ViUInt32 adj);
ViStatus _VI_FUNC TXPPAX_SetSensorCalDate (ViSession instr, ViUInt32 cal, ViUInt32 next);
ViStatus _VI_FUNC TXPPAX_SetSensorGPEepromValues (ViSession instr, ViInt32 _VI_FAR values[]);
ViStatus _VI_FUNC TXPPAX_GetSensorGPEepromValues (ViSession instr, ViInt32 _VI_FAR values[]);


// Utility - Service - Measurement - CAB Measurement
ViStatus _VI_FUNC TXPPAX_GetCurrentArrayMeas (ViSession instr, ViReal64 _VI_FAR array[], ViUInt32 size, ViPUInt32 retCnt);
ViStatus _VI_FUNC TXPPAX_StartCurrentArrayMeas (ViSession instr);
ViStatus _VI_FUNC TXPPAX_SetCurrentArrayMeasParameters (ViSession instr, ViUInt32 periods, ViUInt32 buffers, ViUInt8 trgSrc, ViPUInt32 CABSize);
ViStatus _VI_FUNC TXPPAX_GetCurrentArrayMeasParameters (ViSession instr, ViPUInt32 periods, ViPUInt32 buffers, ViPUInt8 trgSrc, ViPUInt32 CABSize);
ViStatus _VI_FUNC TXPPAX_GetCurrentArrayMeasParametersRange (ViSession instr, ViPUInt32 minPer, ViPUInt32 maxPer, ViPUInt32 defPer, ViPUInt32 minBuf, ViPUInt32 maxBuf, ViPUInt32 defBuf, ViPUInt8 defTrgSrc);


// Utility - Service - Measurement - Single FFT Measurement
ViStatus _VI_FUNC TXPPAX_GetSingleFFTMeas (ViSession instr, ViBoolean block, ViPReal64 val_a0, ViPReal64 val_a1, ViPReal64 val_a2, ViPReal64 phi1, ViPReal64 phi2, ViPUInt32 newMeas);
ViStatus _VI_FUNC TXPPAX_RestartSingleFFTMeas (ViSession instr);
ViStatus _VI_FUNC TXPPAX_SetSingleFFTMeasParameters (ViSession instr, ViUInt32 numPeriod, ViUInt32 numBuf, ViUInt32 numFFT);
ViStatus _VI_FUNC TXPPAX_GetSingleFFTMeasParameters (ViSession instr, ViPUInt32 numPeriod, ViPUInt32 numBuf, ViPUInt32 numFFT);
ViStatus _VI_FUNC TXPPAX_GetSingleFFTMeasParametersRange (ViSession instr, ViPUInt32 minNumPeriod, ViPUInt32 maxNumPeriod, ViPUInt32 defNumPeriod,
                                     	                  						ViPUInt32 minNumBuf,    ViPUInt32 maxNumBuf,    ViPUInt32 defNumBuf,
                                       	                						ViPUInt32 minNumFFT,    ViPUInt32 maxNumFFT,    ViPUInt32 defNumFFT);


// Utility - Service - Measurement - Array FFT Measurement
ViStatus _VI_FUNC TXPPAX_GetArrayFFTMeas (ViSession instr, ViReal64 _VI_FAR a0[], ViReal64 _VI_FAR a1[], ViReal64 _VI_FAR a2[], ViReal64 _VI_FAR phi1[], ViReal64 _VI_FAR phi2[], ViUInt32 arraySize, ViPUInt32 retCnt);
ViStatus _VI_FUNC TXPPAX_StartArrayFFTMeas (ViSession instr);
ViStatus _VI_FUNC TXPPAX_TriggerArrayFFTMeas (ViSession instr);
ViStatus _VI_FUNC TXPPAX_SetArrayFFTMeasParameters (ViSession instr, ViUInt32 numPer, ViUInt32 numBuf, ViUInt32 numFFT, ViUInt32 numMeas, ViUInt32 recRate, ViUInt32 preTrg, ViUInt8 trgSrc);
ViStatus _VI_FUNC TXPPAX_GetArrayFFTMeasParameters (ViSession instr, ViPUInt32 numPer, ViPUInt32 numBuf, ViPUInt32 numFFT, ViPUInt32 numMeas, ViPUInt32 recRate, ViPUInt32 preTrg, ViPUInt8 trgSrc);
ViStatus _VI_FUNC TXPPAX_GetArrayFFTMeasParametersRange (ViSession instr, ViPUInt32 minPer, ViPUInt32 maxPer, ViPUInt32 defPer, ViPUInt32 minBuf, ViPUInt32 maxBuf, ViPUInt32 defBuf, ViPUInt32 minFFT, ViPUInt32 maxFFT, ViPUInt32 defFFT); 
ViStatus _VI_FUNC TXPPAX_GetArrayFFTRecordParametersRange (ViSession instr, ViPUInt32 minMeas, ViPUInt32 maxMeas, ViPUInt32 defMeas, ViPUInt32 minRate, ViPUInt32 maxRate, ViPUInt32 defRate, ViPUInt32 minTrg, ViPUInt32 maxTrg, ViPUInt32 defTrg, ViPUInt8 defTrgSrc);


// Utility - Service - Adjustment - DAC Adjustment
ViStatus _VI_FUNC TXPPAX_SetDacAdjObjectU32U32 (ViSession i, ViUInt8 type, ViUInt32 lCmd, ViUInt32 pCmd, ViUInt8 valid, ViUInt32 dMin, ViUInt32 dMax, ViUInt32 dDef, ViUInt32 _VI_FAR xVal[], ViUInt32 _VI_FAR yVal[], ViUInt32 cnt);
ViStatus _VI_FUNC TXPPAX_SetDacAdjObjectU32FP32 (ViSession i, ViUInt8 type, ViUInt32 lCmd, ViUInt32 pCmd, ViUInt8 valid, ViUInt32 dMin, ViUInt32 dMax, ViUInt32 dDef, ViUInt32 _VI_FAR xVal[], ViReal32 _VI_FAR yVal[], ViUInt32 cnt);
ViStatus _VI_FUNC TXPPAX_SetDacAdjObjectFP32U32 (ViSession i, ViUInt8 type, ViUInt32 lCmd, ViUInt32 pCmd, ViUInt8 valid, ViReal32 dMin, ViReal32 dMax, ViReal32 dDef, ViReal32 _VI_FAR xVal[], ViUInt32 _VI_FAR yVal[], ViUInt32 cnt);
ViStatus _VI_FUNC TXPPAX_SetDacAdjObjectFP32FP32 (ViSession i, ViUInt8 type, ViUInt32 lCmd, ViUInt32 pCmd, ViUInt8 valid, ViReal32 dMin, ViReal32 dMax, ViReal32 dDef, ViReal32 _VI_FAR xVal[], ViReal32 _VI_FAR yVal[], ViUInt32 cnt);

ViStatus _VI_FUNC TXPPAX_GetDacAdjObjectU32U32 (ViSession i, ViUInt8 type, ViUInt32 lCmd, ViUInt32 pCmd, ViPUInt8 valid, ViPUInt32 dMin, ViPUInt32 dMax, ViPUInt32 dDef, ViUInt32 _VI_FAR xVal[], ViUInt32 _VI_FAR yVal[], ViUInt32 size, ViPUInt32 retCnt);
ViStatus _VI_FUNC TXPPAX_GetDacAdjObjectU32FP32 (ViSession i, ViUInt8 type, ViUInt32 lCmd, ViUInt32 pCmd, ViPUInt8 valid, ViPUInt32 dMin, ViPUInt32 dMax, ViPUInt32 dDef, ViUInt32 _VI_FAR xVal[], ViReal32 _VI_FAR yVal[], ViUInt32 size, ViPUInt32 retCnt);
ViStatus _VI_FUNC TXPPAX_GetDacAdjObjectFP32U32 (ViSession i, ViUInt8 type, ViUInt32 lCmd, ViUInt32 pCmd, ViPUInt8 valid, ViPReal32 dMin, ViPReal32 dMax, ViPReal32 dDef, ViReal32 _VI_FAR xVal[], ViUInt32 _VI_FAR yVal[], ViUInt32 size, ViPUInt32 retCnt);
ViStatus _VI_FUNC TXPPAX_GetDacAdjObjectFP32FP32 (ViSession i, ViUInt8 type, ViUInt32 lCmd, ViUInt32 pCmd, ViPUInt8 valid, ViPReal32 dMin, ViPReal32 dMax, ViPReal32 dDef, ViReal32 _VI_FAR xVal[], ViReal32 _VI_FAR yVal[], ViUInt32 size, ViPUInt32 retCnt);

ViStatus _VI_FUNC TXPPAX_ConvertLimits (ViSession instr, ViReal64 min64, ViReal64 max64, ViReal64 def64, ViPReal32 pmin32, ViPReal32 pmax32, ViPReal32 pdef32);


// Utility - Service - Adjustment - ADC Adjustment
ViStatus _VI_FUNC TXPPAX_SetAdcAdjObjectU32U32 (ViSession i, ViUInt8 type, ViUInt32 lCmd, ViUInt32 pCmd, ViUInt8 valid, ViUInt32 dMin, ViUInt32 dMax, ViUInt32 _VI_FAR xVal[], ViUInt32 _VI_FAR yVal[], ViUInt32 cnt);
ViStatus _VI_FUNC TXPPAX_SetAdcAdjObjectU32FP32 (ViSession i, ViUInt8 type, ViUInt32 lCmd, ViUInt32 pCmd, ViUInt8 valid, ViReal32 dMin, ViReal32 dMax, ViUInt32 _VI_FAR xVal[], ViReal32 _VI_FAR yVal[], ViUInt32 cnt);
ViStatus _VI_FUNC TXPPAX_SetAdcAdjObjectFP32U32 (ViSession i, ViUInt8 type, ViUInt32 lCmd, ViUInt32 pCmd, ViUInt8 valid, ViUInt32 dMin, ViUInt32 dMax, ViReal32 _VI_FAR xVal[], ViUInt32 _VI_FAR yVal[], ViUInt32 cnt);
ViStatus _VI_FUNC TXPPAX_SetAdcAdjObjectFP32FP32 (ViSession i, ViUInt8 type, ViUInt32 lCmd, ViUInt32 pCmd, ViUInt8 valid, ViReal32 dMin, ViReal32 dMax, ViReal32 _VI_FAR xVal[], ViReal32 _VI_FAR yVal[], ViUInt32 cnt);

ViStatus _VI_FUNC TXPPAX_GetAdcAdjObjectU32U32 (ViSession i, ViUInt8 type, ViUInt32 lCmd, ViUInt32 pCmd, ViPUInt8 valid, ViPUInt32 dMin, ViPUInt32 dMax, ViUInt32 _VI_FAR xVal[], ViUInt32 _VI_FAR yVal[], ViUInt32 size, ViPUInt32 retCnt);
ViStatus _VI_FUNC TXPPAX_GetAdcAdjObjectU32FP32 (ViSession i, ViUInt8 type, ViUInt32 lCmd, ViUInt32 pCmd, ViPUInt8 valid, ViPReal32 dMin, ViPReal32 dMax, ViUInt32 _VI_FAR xVal[], ViReal32 _VI_FAR yVal[], ViUInt32 size, ViPUInt32 retCnt);
ViStatus _VI_FUNC TXPPAX_GetAdcAdjObjectFP32U32 (ViSession i, ViUInt8 type, ViUInt32 lCmd, ViUInt32 pCmd, ViPUInt8 valid, ViPUInt32 dMin, ViPUInt32 dMax, ViReal32 _VI_FAR xVal[], ViUInt32 _VI_FAR yVal[], ViUInt32 size, ViPUInt32 retCnt);
ViStatus _VI_FUNC TXPPAX_GetAdcAdjObjectFP32FP32 (ViSession i, ViUInt8 type, ViUInt32 lCmd, ViUInt32 pCmd, ViPUInt8 valid, ViPReal32 dMin, ViPReal32 dMax, ViReal32 _VI_FAR xVal[], ViReal32 _VI_FAR yVal[], ViUInt32 size, ViPUInt32 retCnt);


// Utility - Service - Adjustment - Range Objects
ViStatus _VI_FUNC TXPPAX_SetRngObjectU32 (ViSession i, ViUInt32 cmd, ViUInt8 valid, ViUInt32 min, ViUInt32 max, ViUInt32 def);
ViStatus _VI_FUNC TXPPAX_SetRngObjectFP32 (ViSession i, ViUInt32 cmd, ViUInt8 valid, ViReal32 min, ViReal32 max, ViReal32 def);
ViStatus _VI_FUNC TXPPAX_GetRngObjectU32 (ViSession i, ViUInt32 cmd, ViPUInt8 valid, ViPUInt32 min, ViPUInt32 max, ViPUInt32 def);
ViStatus _VI_FUNC TXPPAX_GetRngObjectFP32 (ViSession i, ViUInt32 cmd, ViPUInt8 valid, ViPReal32 min, ViPReal32 max, ViPReal32 def);


// Utility - Service - Adjustment - Value Objects
ViStatus _VI_FUNC TXPPAX_SetValObjectU32 (ViSession instr, ViUInt32 obj, ViUInt32 val);
ViStatus _VI_FUNC TXPPAX_GetValObjectU32 (ViSession instr, ViUInt32 obj, ViPUInt32 pval);
ViStatus _VI_FUNC TXPPAX_SetValObjectFP32 (ViSession instr, ViUInt32 obj, ViReal32 val);
ViStatus _VI_FUNC TXPPAX_GetValObjectFP32 (ViSession instr, ViUInt32 obj, ViPReal32 pval);


// Utility - Service - Adjustment - Service Switch
ViStatus _VI_FUNC TXPPAX_SetServiceSwitch (ViSession instr, ViUInt32 swnum, ViUInt32 val);
ViStatus _VI_FUNC TXPPAX_GetServiceSwitch (ViSession instr, ViUInt32 swnum, ViPUInt32 pval);


// Utility - Service - Adjustment - PAX specific adjustment
ViStatus _VI_FUNC TXPPAX_SetSensorSpeedWindow (ViSession instr, ViUInt8 valid, ViReal32 window);
ViStatus _VI_FUNC TXPPAX_GetSensorSpeedWindow (ViSession instr, ViPUInt8 pvalid, ViPReal32 pwindow);
ViStatus _VI_FUNC TXPPAX_SetSensorAzimuthOffset (ViSession instr, ViUInt8 valid, ViReal32 offset);
ViStatus _VI_FUNC TXPPAX_GetSensorAzimuthOffset (ViSession instr, ViPUInt8 pvalid, ViPReal32 poffset);




#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif

#endif	/* __TXPPAX_HEADER */

/****************************************************************************
  End of Header file
****************************************************************************/
