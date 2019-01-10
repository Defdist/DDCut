#ifdef __APPLE__
#include "GhostGunnerFinder.h"

#include "Logging/Logger.h"

#include <list>
#include <string>

// TODO: Clean these up:
#include <IOKit/IOKitLib.h>
#include <IOKit/usb/IOUSBLib.h>
#include <sys/param.h>
#include <paths.h>
#include <IOKit/IOBSD.h>
#include <IOKit/serial/IOSerialKeys.h>
#include <CoreFoundation/CFNumber.h>
#include <IOKit/graphics/IOGraphicsLib.h>
#include <iomanip>
#include <sstream>

/*
https://developer.apple.com/library/archive/documentation/DeviceDrivers/Conceptual/AccessingHardware/AH_Finding_Devices/AH_Finding_Devices.html#//apple_ref/doc/uid/TP30000379-BAJDAJDJ
To find devices in the I/O Registry, you perform the following steps:

1. Get the I/O Kit master port to communicate with the I/O Kit.
2. Find the appropriate keys and values that sufficiently define the target device or set of devices.
3. Use the key-value pairs to create a matching dictionary.
4. Use the matching dictionary to look up matching devices in the I/O Registry.
*/
std::list<GhostGunner> GhostGunnerFinder::GetAvailableGhostGunners() const
{
	std::list<GhostGunner> availableGhostGunners;

	/* set up a matching dictionary for the class */
	CFMutableDictionaryRef matchingDict = IOServiceMatching(kIOUSBDeviceClassName);
	if (matchingDict == NULL)
	{
		return availableGhostGunners; // fail
	}

	/* Now we have a dictionary, get an iterator.*/
	io_iterator_t iter;
	kern_return_t kr = IOServiceGetMatchingServices(kIOMasterPortDefault, matchingDict, &iter);
	if (kr != KERN_SUCCESS)
	{
		return availableGhostGunners;
	}

	/* iterate */
	io_service_t device;
	while ((device = IOIteratorNext(iter)))
	{
		CFMutableDictionaryRef dict = NULL;
		if (IORegistryEntryCreateCFProperties(device, &dict, kCFAllocatorDefault, 0) == KERN_SUCCESS)
		{
			// Find device with vendor Id == 2341 (Arduino) && PID_0043 OR PID_7523
			const CFNumberRef vendorIDRef = (CFNumberRef)CFDictionaryGetValue(dict, CFSTR("idVendor"));
			const CFNumberRef productIDRef = (CFNumberRef)CFDictionaryGetValue(dict, CFSTR("idProduct"));
			const CFNumberRef locationIDRef = (CFNumberRef)CFDictionaryGetValue(dict, CFSTR("locationID"));
            const CFStringRef serialNumberRef = (CFStringRef)CFDictionaryGetValue(dict, CFSTR(kUSBSerialNumberString));
			if (vendorIDRef && productIDRef && locationIDRef && serialNumberRef)
			{
				unsigned int vendorID, productID;
				CFNumberGetValue(vendorIDRef, kCFNumberSInt32Type, &vendorID);
				CFNumberGetValue(productIDRef, kCFNumberSInt32Type, &productID);
				if ((vendorID == std::stoul("2341", nullptr, 16) && productID == std::stoul("43", nullptr, 16)) || (vendorID == std::stoul("1A86", nullptr, 16) && productID == std::stoul("7523", nullptr, 16)))
				{
					unsigned int locationID;
					CFNumberGetValue(locationIDRef, kCFNumberSInt32Type, &locationID);

					std::stringstream stream;
					stream << std::hex << locationID;
					std::string locationStr(stream.str());

					// convert the serial number string object into a C-string
					const CFIndex bufferSize = CFStringGetMaximumSizeForEncoding(CFStringGetLength(serialNumberRef), kCFStringEncodingMacRoman) + sizeof('\0');
					std::vector<char> serialNumberBuf(bufferSize);
					CFStringGetCString(serialNumberRef, serialNumberBuf.data(), bufferSize, kCFStringEncodingMacRoman);
                    const std::string serialNumber = std::string(serialNumberBuf.begin(), serialNumberBuf.end());

					//Logger::GetInstance().Log("VendorID: " + std::to_string(vendorID) + " ProductID: " + std::to_string(productID) + " LocationID: " + locationStr + " SerialNumber: " + serialNumber);
                    
                    int numTrailingZeros = 0;
                    for (int i = locationStr.length() - 1; i >= 0; i--)
                    {
                        if (locationStr[i] == '0')
                        {
                            numTrailingZeros++;
                        }
                        else
                        {
                            break;
                        }
                    }

                    const std::string path = "/dev/cu.usbmodem" + locationStr.substr(0, locationStr.length() - numTrailingZeros) + "1";
                    availableGhostGunners.push_back(GhostGunner(path, serialNumber));

				}
			}


			CFRelease(dict);
		}

		IOObjectRelease(device);
	}

	//Logger::GetInstance().Log("Finished searching for ghostgunners: " + std::to_string(availableGhostGunners.size()) + " found.");

	IOObjectRelease(iter);

	return availableGhostGunners;
}
#endif
