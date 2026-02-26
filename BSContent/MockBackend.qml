import QtQuick 6.5

// This defines a fake "C++ Backend" entirely in QML for Qt Design Studio preview purposes.
// It exposes exactly the same properties a real C++ backend would.
QtObject {
    id: backend

    // Properties
    property string targetIp: "192.168.1.100"
    property bool isConnected: false
    property bool isAcquiring: false
    property string currentPoint: "P004"
    property int progressPercent: 0

    property real batteryVoltage: 12.4
    property real internalTemp: 42.8
    property real signalStrength: -68.0

    // For simplicity, we just expose single scaling values for the waveforms
    // In a real C++ backend, these would be QVariantLists, but in QtDS pure QML mock
    // we just use a height multiplier scale to make the UI jump.
    property real recvScale: 1.0
    property real sendScale: 1.0
    property real offScale: 1.0

    // Invokable Methods
    function connectDevice() {
        if (isConnected) {
            isConnected = false;
            isAcquiring = false;
            simTimer.stop();
            console.log("Disconnected.");
        } else {
            isConnected = true;
            batteryVoltage = 12.5;
            internalTemp = 38.0;
            console.log("Connected to " + targetIp);
        }
    }

    function startAcquisition() {
        if (!isConnected) {
            console.warn("Cannot start: Device not connected!");
            return;
        }
        if (isAcquiring) {
            // Act as Stop button
            isAcquiring = false;
            simTimer.stop();
            console.log("Acquisition stopped.");
        } else {
            isAcquiring = true;
            progressPercent = 0;
            simTimer.start();
            console.log("Started TEM acquisition on " + currentPoint);
        }
    }
    
    function skipPoint() {
        isAcquiring = false;
        simTimer.stop();
        currentPoint = "P005";
        progressPercent = 0;
        console.log("Skipped to next point: P005");
    }

    // internal simulation timer
    property Timer _timer: Timer {
        id: simTimer
        interval: 100 // 10fps
        repeat: true
        onTriggered: {
            backend.progressPercent += 1;
            if (backend.progressPercent >= 100) {
                backend.progressPercent = 100;
                backend.isAcquiring = false;
                stop();
                console.log("Acquisition finished for " + backend.currentPoint);
            }

            // Jitter sensor data
            backend.batteryVoltage -= 0.001;
            backend.internalTemp += 0.05;

            // Generate scale noise (0.8 ~ 1.2) for waveforms to dance
            backend.recvScale = 0.8 + Math.random() * 0.4;
            backend.sendScale = 0.9 + Math.random() * 0.2;
            backend.offScale = 0.8 + Math.random() * 0.4;
        }
    }
}
