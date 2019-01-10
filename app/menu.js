const {Menu} = require('electron')

module.exports = function UpdateMenu()
{
	const FileMenu = 
	{
		label: 'File',
		submenu:
		[
			{
				label: 'Open',
			},
			{
				label: 'Save'
			},
			{
				label: 'Save As'
			},
			{
				label: 'Close'
			}
		]
	}
	
	const GGMenu = 
	{
		label: 'GG',
		submenu: 
		[
			{
				label: 'Connect',
				click: function()
				{
					
				}
			},
			{
				label: 'Firmware',
				submenu:
				[
					{
						label: 'Upload',
						click: function()
						{
							
						}
					},
					{
						label: 'Version',
						click: function()
						{
							
						}
					}
				]
			},
			{
				label: 'Settings',
				submenu:
				[
					{
						label: 'CommTimeout',
						click: function()
						{
							
						}
					},
					{
						label: 'Cutting Speed Adj',
						click: function()
						{
							
						}
					}
				]
			}
		]
	};
	
	const HelpMenu = 
	{
		label: 'Help',
		submenu: 
		[
			{
				label: 'Search',
				click: function()
				{
					
				}
			},
			{
				label: 'View Manual',
				click: function()
				{
					
				}
			},
			{
				label: 'Visit Support Page',
				click: function()
				{
					
				}
			},
			{
				label: 'Contact Customer Support',
				click: function()
				{
					
				}
			}
		]
	};
	
	
	const menuTemplate = [FileMenu, GGMenu, HelpMenu];
	
	const menu = Menu.buildFromTemplate(menuTemplate)
	
	Menu.setApplicationMenu(menu)
}