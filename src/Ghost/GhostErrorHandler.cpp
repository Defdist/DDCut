#include "GhostErrorHandler.h"
#include "DDLogger/DDLogger.h"
#include "ProbeHelper.h"
#include "Common/OSUtility.h"

std::string GhostErrorHandler::GetErrorMessage(GhostConnection& connection, const GhostException& exception)
{
	const std::string errorText = GetErrorMessage_Internal(connection, exception);
	DDLogger::Log("GhostErrorHandler::GetErrorMessage - " + errorText);
	return errorText;
}

std::string GhostErrorHandler::GetErrorMessage_Internal(GhostConnection& connection, const GhostException& exception)
{
	//EnableWindow(GetDlgItem(hw, IDR_ESTOP), FALSE);
	if (connection.getState() & Ghost::Status::GS_TIMEOUT)
	{
		connection.reset();
		return "Machine is timed-out due to an operation not completing";
		//OSUtility::ShowMessageBox("Error", "Machine is timed-out due to an operation not completing");
	}
	else if (connection.getState() & Ghost::Status::GS_ERROR)
	{
		std::size_t found = connection.GetError().find("Probe fail");
		if (found != std::string::npos)
		{
			return HandleProbeFailure(connection);
		}
		else
		{
			if (connection.GetError().find("Not idle") != std::string::npos)
			{
				//string s;
				std::vector<std::string> vec;
				vec.push_back("$X"); // Kill Alarm Clock
				connection.send(vec);
				WriteToGhostGunner(connection);
			}

			connection.reset();
			std::string locked_message;

			std::size_t found = connection.GetError().find("Homing fail");
			if (found != std::string::npos)
			{
				locked_message = "Machine is locked due to an error:\n" + connection.GetError() + "\n\nPlease make sure there is power to the unit.";
			}
			else
			{
				found = connection.GetError().find("soft limit");
				if (found != std::string::npos)
				{
					locked_message = "Machine is locked due to an error:\n" + connection.GetError() + "\n\nHardware limit: a limit switch was engaged unexpectedly.\nSoftware limit: move command outside of software limits for work space.";
				}
				else
				{
					locked_message = "Machine is locked due to an error:\n" + connection.GetError();
				}
			}

			//OSUtility::ShowMessageBox("Error", locked_message);

			if (connection.GetError().find("Not idle") != std::string::npos)
			{
				//state.jobIndex = state.jobIndex - 1;
			}

			return locked_message;
		}
	}
	/*else if (state.state == WIZCHOOSEGHOST)
	{
	MessageBox(state.hw, "Ghost Gunner did not connect", "Error", MB_ICONERROR | MB_OK);
	//EnableWindow(GetDlgItem(state.hw, IDR_NEXT), TRUE);
	//DDFileManager::GetInstance().SetSelectedFile(nullptr);
	}*/
	else if (exception.getType() == GhostException::M101_FAIL)
	{
		DDLogger::Log("GhostErrorHandler::GetErrorMessage_Internal - M101 Failure");
		DDLogger::Flush();
		//char *ch = ghostConnection.GetError().substr(8,1);
		//string axis (ch);
		//                    string msg = "M101 command failed with result: "+ ghostConnection.GetError().substr(8,1) +" axis.  Adjustment for Lower is out of tolerance and must be re-adjusted.\nDDCut will abort this job. ";
		//string msg = "M101 command failed with result: The frame/lower is out of tolerance for the "+ ghostConnection.GetError().substr(8,1) +" axis\n\nPlease adjust the frame/lower and try again.\n\nIf this error persists you may need to contact Ghost Gunner technical support or run the M100.DD file.";

		const std::string msg = "The frame/lower is out of tolerance for the " 
			+ exception.GetRawDetailMessage()// connection.GetError().substr(8, 1) 
			+ " axis\n\nPlease adjust the frame/lower and try again.\n\nIf this error persists you may need to contact Ghost Gunner technical support or run the M100 milling file.\n\nThe workpiece is not positioned within tolerance for the " 
			+ exception.GetRawDetailMessage()// connection.GetError().substr(8, 1) 
			+ " axis\n\n Please adjust the workpiece and try again.  ";
		return msg;
	}
	else if (!connection.GetError().empty())
	{
		return std::string("Machine is locked due to an error:\n") + connection.GetError();
	}
	else
	{
		return std::string("Machine is locked due to an error:\n") + exception.what();
	}
}

void GhostErrorHandler::HandleFailure(GhostConnection& ghostConnection) const
{
	//EnableWindow(GetDlgItem(hw, IDR_ESTOP), FALSE);
	if (ghostConnection.getState() & Ghost::Status::GS_TIMEOUT)
	{
		ghostConnection.reset();
		OSUtility::ShowMessageBox("Error", "Machine is timed-out due to an operation not completing");
	}
	else if (ghostConnection.getState() & Ghost::Status::GS_ERROR)
	{
		std::size_t found = ghostConnection.GetError().find("Probe fail");
		if (found != std::string::npos)
		{
			HandleProbeFailure(ghostConnection);
		}
		else
		{
			if (ghostConnection.GetError().find("Not idle") != std::string::npos)
			{
				//string s;
				std::vector<std::string> vec;
				vec.push_back("$X"); // Kill Alarm Clock
				ghostConnection.send(vec);
				WriteToGhostGunner(ghostConnection);
			}

			ghostConnection.reset();
			std::string locked_message;

			std::size_t found = ghostConnection.GetError().find("Homing fail");
			if (found != std::string::npos)
			{
				locked_message = "Machine is locked due to an error:\n" + ghostConnection.GetError() + "\n\nPlease make sure there is power to the unit.";
			}
			else
			{
				found = ghostConnection.GetError().find("soft limit");
				if (found != std::string::npos)
				{
					locked_message = "Machine is locked due to an error:\n" + ghostConnection.GetError() + "\n\nHardware limit: a limit switch was engaged unexpectedly.\nSoftware limit: move command outside of software limits for work space.";
				}
				else
				{
					locked_message = "Machine is locked due to an error:\n" + ghostConnection.GetError();
				}
			}

			OSUtility::ShowMessageBox("Error", locked_message);

			if (ghostConnection.GetError().find("Not idle") != std::string::npos)
			{
				//state.jobIndex = state.jobIndex - 1;
			}
		}
	}
	/*else if (state.state == WIZCHOOSEGHOST)
	{
	MessageBox(state.hw, "Ghost Gunner did not connect", "Error", MB_ICONERROR | MB_OK);
	//EnableWindow(GetDlgItem(state.hw, IDR_NEXT), TRUE);
	//DDFileManager::GetInstance().SetSelectedFile(nullptr);
	}*/
	else
	{

		std::size_t found = ghostConnection.GetError().find("M101FAIL");
		if (found != std::string::npos)
		{
			//char *ch = ghostConnection.GetError().substr(8,1);
			//string axis (ch);
			//                    string msg = "M101 command failed with result: "+ ghostConnection.GetError().substr(8,1) +" axis.  Adjustment for Lower is out of tolerance and must be re-adjusted.\nDDCut will abort this job. ";
			//string msg = "M101 command failed with result: The frame/lower is out of tolerance for the "+ ghostConnection.GetError().substr(8,1) +" axis\n\nPlease adjust the frame/lower and try again.\n\nIf this error persists you may need to contact Ghost Gunner technical support or run the M100.DD file.";

			const std::string msg = "The frame/lower is out of tolerance for the " + ghostConnection.GetError().substr(8, 1) + " axis\n\nPlease adjust the frame/lower and try again.\n\nIf this error persists you may need to contact Ghost Gunner technical support or run the M100 milling file.\n\nThe workpiece is not positioned within tolerance for the " + ghostConnection.GetError().substr(8, 1) + " axis\n\n Please adjust the workpiece and try again.  ";
			OSUtility::ShowMessageBox("Operation Aborted", msg);
		}
		else
		{
			const std::string msg = "Machine is locked due to an error " + ghostConnection.GetError();
			OSUtility::ShowMessageBox("Operation Aborted", msg);
		}

		ghostConnection.reset();
		Sleep(1000);
		ghostConnection.send("$?");
		ghostConnection.WriteCache();
		Sleep(1000);
		std::string s;
		while (ghostConnection.ReadLine(s))
		{
			DDLogger::Log(s);
		}

		//DDFileManager::GetInstance().SetSelectedFile(nullptr);
		//state.state = WIZEND;
	}
}

std::string GhostErrorHandler::HandleProbeFailure(GhostConnection& ghostConnection)
{
	ghostConnection.ClearProbeStatus();
	//state.jobIndex = state.jobIndex - 1;

	std::vector<std::string> vec;

	vec.push_back("S0");
	vec.push_back("M5"); // (Turn off Spindle)

	// assign saved coord to commands
	char xx[16];
	sprintf(xx, "%.2f", ghostConnection.getXCoordinate());
	char yy[16];
	sprintf(yy, "%.2f", ghostConnection.getYCoordinate());
	char zz[16];
	sprintf(zz, "%.2f", ghostConnection.getZCoordinate());
	std::string x(xx), y(yy), z(zz);

	vec.push_back("G53 G0 Z-1  (pulls the cutting tool away from part... note I don't use Z0 because that could trip the limit switch)");
	vec.push_back("G53 G0 X" + x + " Y" + y + "    (places cutting tool in correct XY)");
	vec.push_back("G53 G0 Z" + z + "   (at this point we're right back where we started prior to the first probe in the file)");

	ghostConnection.ResetIdleTime();
	ghostConnection.send(vec);
	ghostConnection.setTimeout(std::chrono::seconds(15));

	WriteToGhostGunner(ghostConnection);

	bool probecleared = false;
	//msg = "A probe error occurred.  Please verify the red probe lead isn't shorted to the chassis.  If this error occurred while probing a part, please verify part placement and vacuum any metal shavings that might be electrically conducting between the part and the build plate, then press OK to retry the probe, or Cancel to abort.";
	const std::string message = "Probe signal error. Verify probe lead is charging workpiece with 5V DC. The workpiece may be shorted to the t-slot platform. ";
	return message;
	/*while (!probecleared)
	{
		if (OSUtility::ShowOkCancelMessageBox("Probe Error", message))
		{
			try
			{
				probecleared = ProbeHelper().IsProbeStateClear(ghostConnection);
				//message = "Probe is still shorted; please vacuum any metal shavings around the lower receiver, then press OK, or press Cancel to abort.";
			}
			catch (GhostException e)
			{
				ghostConnection.reset();
				probecleared = true;
			}
		}
		else
		{
			ghostConnection.reset();
			//OSUtility::ShowMessageBox("DDCut", "Operation Aborted");
			return "Operation Aborted";
		}
	}*/
}

bool GhostErrorHandler::WriteToGhostGunner(GhostConnection& ghostConnection)
{
	bool hit = true;
	bool cleanup = true;
	std::string s;
	while (true)
	{
		try
		{
			if (!ghostConnection.WriteCache())
			{
				if (cleanup && !(ghostConnection.getState() & Ghost::Status::GS_LOCKED))
				{
					// Wait for 0.1 seconds (http://linuxcnc.org/docs/html/gcode/g-code.html#gcode:g4)
					ghostConnection.send("G4 P0.1");
					cleanup = false;
				}
				else
				{
					break;
				}
			}

			hit = false;

			while (ghostConnection.ReadLine(s))
			{
				hit = true;
				DDLogger::Log(s);
			}

			if (!hit)
			{
				Sleep(10);
			}

			if (ghostConnection.getState() & Ghost::Status::GS_TIMEOUT)
			{
				DDLogger::Log("timeout exceeded in probe recovery");
				break;
			}
		}
		catch (GhostException &e)
		{
			ghostConnection.reset();
			return false;
		}
	}

	return true;
}