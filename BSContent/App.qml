import QtQuick 6.5
import BS

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "TEM Acquisition (Mock Data Mode)"

    // Our pseudo C++ backend written in QML for QtDS design purposes
    MockBackend { id: mockBackend }

    Screen01 {
        id: mainScreen

        // Inject the backend property downwards. 
        // In Screen01.ui.qml we will declare `property QtObject backend`
        backend: mockBackend
    }
}
