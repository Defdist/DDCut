
//////////////////////////////////////////////////////
// Dashboard
//////////////////////////////////////////////////////
function ShowDashboardWalkthrough(machine_name) {
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
                intro: `WELCOME TO THE ${machine_name.toUpperCase()} DASHBOARD INTERFACE!`
            },
            {
                element: '#run',
                intro: `Click RUN to select and run a milling file on your ${machine_name}.'`
            },
            {
                element: '#store',
                intro: `Purchase new jigs, lowers and tooling from the ${machine_name} Store.`,
                position: 'top'
            },
            {
                element: '#GGStatus',
                intro: `The status bar displays ${machine_name} status.`
            },
            {
                element: '#settings',
                intro: 'Access settings and update firmware.',
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
function ShowMillingWalkthrough(machine_name) {
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
                intro: `WELCOME TO YOUR ${machine_name.toUpperCase()} OPERATION SCREEN!`
            },
            {
                element: '#steps',
                intro: "This displays the milling file and all the steps in the file.",
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
