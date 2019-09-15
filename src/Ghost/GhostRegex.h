#pragma once

#include <regex>

namespace Ghost
{
	namespace Regex
	{
		static const std::regex RXSTART = std::regex("^Grbl \\d+\\.\\d+.*\r?\n?");
		static const std::regex RXERROR = std::regex("^error: (.*)\r?\n?");
		static const std::regex RXOVERFLOW = std::regex("^Line overflow\r?\n?");
		static const std::regex RXNOTIDLE = std::regex("^Not idle\r?\n?");
		static const std::regex RXOK = std::regex("^ok\r?\n?");
		static const std::regex RXALARM = std::regex("^ALARM: (.*)\r?\n?");
		//static const std::regex RXM1XX=std::regex("^M(1\\d\\d)(.*)",std::regex_constants::icase);
		static const std::regex RXM1XX = std::regex("^M(1\\d\\d)(.*)", std::regex_constants::icase);
		static const std::regex RXXYZ = std::regex("^(X|Y|Z)(-?\\d*\\.?\\d+)(.*)", std::regex_constants::icase);
		static const std::regex RXPRB = std::regex("^\\[PRB:(-?\\d*\\.?\\d+),(-?\\d*\\.?\\d+),(-?\\d*\\.?\\d+):(-?\\d*\\.?\\d+).*", std::regex_constants::icase);
		static const std::regex RXPRBV1 = std::regex("^\\[PRB:(-?\\d*\\.?\\d+),(-?\\d*\\.?\\d+),(-?\\d*\\.?\\d+):(-?\\d*\\.?\\d+).*", std::regex_constants::icase);
		static const std::regex RXSTATUS = std::regex("^<(\\w+),(\\w+):(-?\\d+\\.?\\d+),(-?\\d+\\.?\\d+),(-?\\d+\\.?\\d+),(\\w+):(-?\\d+\\.?\\d+),(-?\\d+\\.?\\d+),(-?\\d+\\.?\\d+),(\\w+):(\\d),(\\w+):(\\d),(\\w+):(\\d),(\\w+):(\\d+)\\|(\\d)\\|(\\d+)>.*", std::regex_constants::icase);
		static const std::regex CMDFEEDRATE = std::regex("^.*F(\\d+).*", std::regex_constants::icase);
		static const std::regex RXWCS = std::regex("^\\[(.?\\d+):(-?\\d*\\.?\\d+),(-?\\d*\\.?\\d+),(-?\\d*\\.?\\d+).*", std::regex_constants::icase);
		//static const std::regex RXTLO=std::regex("^\\[(.?\\d+):(-?\\d*\\.?\\d+).*",std::regex_constants::icase);

		// TODO: Confirm these are still correct
		static const std::regex RXDISABLED = std::regex("^\\[Disabled\\]\r?\n?"); // WAS: std::regex("^\\[Disabled]\n?");
		static const std::regex RXENABLED = std::regex("^\\[Enabled\\]\r?\n?"); // WAS: std::regex("^\\[Enabled]\n?");
		static const std::regex RXLOCKED = std::regex("^\\[.*unlock\\]\r?\n?"); // WAS: std::regex("^\\[.*unlock]\n?");


		static std::regex RXTRUE("^t(rue)?$", std::regex_constants::icase);
		static std::regex RXBMP("^.*BMP$", std::regex_constants::icase);
		static std::regex RXJPEG("^.*(JPEG|JPG)$", std::regex_constants::icase);
		static std::regex RXSTRIP("^\\s*(.*\\w)\\s*$");


		static std::regex RXGCODE = std::regex("^G0*(\\d+).*", std::regex_constants::icase);
		static std::regex RXMCODE = std::regex("^M(\\d+).*", std::regex_constants::icase);
		static std::regex RXAFS = std::regex("^[FIJKLNPRSTXYZ].*", std::regex_constants::icase);
		static std::regex RXGRBL = std::regex("^(\\$(\\$|#|[GINCXH?]|\\d).*|[~!?])");
	}
}