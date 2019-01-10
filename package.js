const path = require('path');

if (process.platform == 'win32')
{
	var child_process = require('child_process');
	child_process.execSync("npm install && electron-packager ./app --arch=ia32 --out=dist --overwrite --icon=app/UI/img/logo.ico  --prune=true", {stdio:[0,1,2]});
	
	const electronInstaller = require('electron-winstaller');
	
	console.log("Creating installer. This will take 2-3 minutes.");
	
	resultPromise = electronInstaller.createWindowsInstaller({
		appDirectory: path.join(__dirname, '/dist/ddcut2-win32-ia32'),
		outputDirectory: path.join(__dirname, '/dist/windows'),
		authors: 'Defense Distributed',
		exe: 'DDCut2.exe',
		iconUrl: path.join(__dirname, '/app/UI/img/logo.ico'),
		setupExe: 'DDSetup.exe',
		setupIcon: path.join(__dirname, '/app/UI/img/logo.ico')
	  });
	 
	resultPromise.then(() => console.log("Success!"), (e) => console.log('Fail: ${e.message}'));
}
else if (process.platform == 'darwin')
{
	var child_process = require('child_process');
	child_process.execSync("cd ./app && npm install && cd .. && npm install && electron-packager ./app --out=dist --overwrite", {stdio:[0,1,2]});
}