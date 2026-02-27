import QtQuick 6.5
import QtQuick.Dialogs
import QtQuick.Controls
import BS

Window {
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    visibility: Window.Maximized

    visible: true
    title: "TEM Acquisition (Mock Data Mode)"

    // Our pseudo C++ backend written in QML for QtDS design purposes
    MockBackend { id: mockBackend }
    
    // Globally accessible backend for top-level dialogs
    property var activeBackend: typeof cppBackend !== "undefined" ? cppBackend : mockBackend
    
    // UI Feedback Dialog
    MessageDialog {
        id: msgDialog
        title: "Project Operation"
        buttons: MessageDialog.Ok
    }
    
    // Dialog for creating a new SQLite project database
    FileDialog {
        id: newProjectDialog
        title: "Create New Project DB"
        fileMode: FileDialog.SaveFile
        nameFilters: ["SQLite Database (*.sqlite)", "All Files (*)"]
        onAccepted: {
            console.log("New Project Dialog Accepted. Selected File: " + selectedFile)
            if (!activeBackend) {
                console.error("Backend is null or undefined!")
                msgDialog.text = "Error"
                msgDialog.informativeText = "Internal Error: Backend is not connected."
                msgDialog.open()
                return
            }
            var success = activeBackend.createProjectDB(selectedFile)
            console.log("createProjectDB returned: " + success)
            if (success) {
                msgDialog.text = "Success!"
                msgDialog.informativeText = "Project database created successfully."
            } else {
                msgDialog.text = "Error"
                msgDialog.informativeText = "Failed to create project database. Check file permissions or path."
            }
            msgDialog.open()
        }
    }

    // Dialog for opening an existing SQLite project database
    FileDialog {
        id: openProjectDialog
        title: "Open Existing Project DB"
        fileMode: FileDialog.OpenFile
        nameFilters: ["SQLite Database (*.sqlite)", "All Files (*)"]
        onAccepted: {
            console.log("Open Project Dialog Accepted. Selected File: " + selectedFile)
            if (!activeBackend) {
                console.error("Backend is null or undefined!")
                msgDialog.text = "Error"
                msgDialog.informativeText = "Internal Error: Backend is not connected."
                msgDialog.open()
                return
            }
            var success = activeBackend.openProjectDB(selectedFile)
            console.log("openProjectDB returned: " + success)
            if (success) {
                msgDialog.text = "Success!"
                msgDialog.informativeText = "Project database opened successfully."
            } else {
                msgDialog.text = "Error"
                msgDialog.informativeText = "Failed to open project database."
            }
            msgDialog.open()
        }
    }

    ScrollView {
        anchors.fill: parent
        contentWidth: 1920
        contentHeight: 1080
        clip: true

        Screen01 {
            id: mainScreen
            width: 1920
            height: 1080

            // Inject the backend property downwards. 
            // Use real C++ backend if injected by main.cpp, otherwise fallback to QtDS MockBackend.
            backend: activeBackend
            
            // Bind the New/Open buttons from Screen01.ui.qml to the Dialogs
            btnNewProject.onClicked: newProjectDialog.open()
            btnOpenProject.onClicked: openProjectDialog.open()
            
            onOpenPlaybackWindow: {
                var component = Qt.createComponent("PlaybackWindow.qml");
                if (component.status === Component.Ready) {
                    var window = component.createObject(parent);
                    window.show();
                } else {
                    console.error("PlaybackWindow component is not ready. Error: " + component.errorString());
                }
            }
            
            // Bind the TCP Connect toggle
            btnConnectDevice.onClicked: {
                if (activeBackend) {
                    if (activeBackend.connectionState === 0) {
                        activeBackend.connectDevice()
                    } else {
                        activeBackend.disconnectDevice()
                    }
                }
            }
            
            // Bind Acquisition controls
            btnAcquire.onClicked: if (activeBackend) activeBackend.startAcquisition()
            btnStop.onClicked: if (activeBackend) activeBackend.stopAcquisition()
            btnCopyParams.onClicked: if (activeBackend) activeBackend.copyPreviousPointParams()

            // Bind Parameter Inputs
            inputPointId.onEditingFinished: if(activeBackend) activeBackend.currentPoint = inputPointId.text
            inputSendCurrent.onEditingFinished: if(activeBackend) activeBackend.sendCurrent = parseFloat(inputSendCurrent.text)
            inputSampleRate.onEditingFinished: if(activeBackend) activeBackend.sampleRate = parseInt(inputSampleRate.text)
            inputStackCount.onEditingFinished: if(activeBackend) activeBackend.stackCount = parseInt(inputStackCount.text)
            inputSampleTime.onEditingFinished: if(activeBackend) activeBackend.sampleTimeLength = parseInt(inputSampleTime.text)
            inputCustomParams.onEditingFinished: if(activeBackend) activeBackend.customParams = inputCustomParams.text

            
            // Listen to Backend Logs/Errors for popups
            Connections {
                target: activeBackend
                function onLogMessage(msg, isWarning) {
                    if (isWarning && msg.indexOf("TCP") !== -1) {
                        msgDialog.title = "TCP Connection Error"
                        msgDialog.text = "Connection Failed"
                        msgDialog.informativeText = msg
                        msgDialog.open()
                    }
                }
            }
        }
    }
}
