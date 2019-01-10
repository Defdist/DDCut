var currentSection = "";
var sectionInitialized = false;

function UpdateMenu(sectionId)
{
	if (sectionId == "Dashboard")
    {
        $("#MenuOpen").removeClass("inactive");
        $("#MenuUpdates").removeClass("inactive");
	}
	else
    {
        $("#MenuOpen").addClass("inactive");
        $("#MenuUpdates").addClass("inactive");
	}
}

function ShowSection(sectionId)
{
	var imports = document.querySelectorAll('link[rel="import"]');

	var node = Array.from(imports).map( (link) => {
		return link.import.querySelector('#' + sectionId);
	}).filter( (val) => {
		return val !== null;
	})[0];

	var wrapper = document.getElementById("wrapper");
	wrapper.removeChild(wrapper.childNodes[0]); 
	wrapper.appendChild(node.cloneNode(true));
	
	currentSection = sectionId;
	
	UpdateMenu(sectionId);
	sectionInitialized = false;
}