
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
                intro: "WELCOME TO YOUR GHOST GUNNER DASHBOARD INTERFACE!"
            },
            {
                element: '#run',
                intro: "This is where you run the most recent DD file."
            },
            {
                element: '#store',
                intro: 'This is where you buy new DD files from Defense Distributed.',
                position: 'top'
            },
            {
                element: '#GGStatus',
                intro: 'This is your status bar. This displays the status of your GhostGunner.'
            },
            {
                element: '#settings',
                intro: "Here you can access settings for firmware and feedrate percentage.",
                position: 'top'
            },
            {
                element: '#support',
                intro: 'Here you can access walkthroughs, help center, or contact the support team.'
            },
            {
                intro: 'You have finished your tour of the dashboard interface. This can always be revisited by selecting the ? in the bottom corner.'
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
                intro: 'You have finished your tour of the dashboard interface. This can always be revisited by selecting the ? in the bottom corner.'
            }
        ]
    });
    intro.start();
}