
//////////////////////////////////////////////////////
// Dashboard
//////////////////////////////////////////////////////
function ShowDashboardWalkthrough() {
    var intro = introJs();
    intro.setOptions({
        showStepNumbers: false,
        exitOnOverlayClick: false,
        hidePrev: true,
        hideNext: true,
        buttonClass: "WalkthroughButton",
        disableInteraction: true,
        highlightClass: "WalkthroughHighlight",
        tooltipClass: "WalkthroughTooltip",
        doneLabel: "End Tour",
        showBullets: false,
        steps: [
            {
                intro: "WELCOME TO THE GHOST GUNNER DASHBOARD INTERFACE!"
            },
            {
                element: '#run',
                intro: "Click RUN to select and run a DD file on your Ghost Gunner."
            },
            {
                element: '#store',
                intro: 'Purchase new jigs, lowers and tooling from the Ghost Gunner Store.',
                position: 'top'
            },
            {
                element: '#GGStatus',
                intro: 'The status bar displays Ghost Gunner status.'
            },
            {
                element: '#settings',
                intro: "Access settings and update firmware.",
                position: 'top'
            },
            {
                element: '#support',
                intro: 'Get help, access walkthroughs, or contact the support team.'
            },
            {
                intro: 'End of tour. To revisit the tour, click the "Support" button in the bottom right and select "\'How- To\' Walkthrough"'
            }
        ]
    });
    intro.start();
}

//////////////////////////////////////////////////////
// Milling
//////////////////////////////////////////////////////
function ShowMillingWalkthrough() {
    var intro = introJs();
    intro.setOptions({
        showStepNumbers: false,
        exitOnOverlayClick: false,
        hidePrev: true,
        hideNext: true,
        buttonClass: "WalkthroughButton",
        disableInteraction: true,
        highlightClass: "WalkthroughHighlight",
        tooltipClass: "WalkthroughTooltip",
        doneLabel: "End Tour",
        showBullets: false,
        steps: [
            {
                intro: "WELCOME TO YOUR GHOST GUNNER OPERATION SCREEN!"
            },
            {
                element: '#steps',
                intro: "This displays the DD file and all the steps in the file.",
                position: 'right'
            },
            {
                element: '#middle_section',
                intro: "This area displays the details for each step.",
            },
            {
                element: '#image',
                intro: 'This area displays any images that accompany the step details. You can switch between the image and the raw output.',
                position: 'top'
            },
            {
                intro: 'You have finished your tour of the operation screen. This can always be revisited by selecting the ? in the bottom corner.'
            }
        ]
    });
    intro.start();
}
