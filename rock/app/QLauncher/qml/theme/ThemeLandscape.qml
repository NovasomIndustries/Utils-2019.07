import QtQuick 2.0
import com.cai.qlauncher 1.0 as QL
import config 1.0 as Config
import QtQuick.Dialogs 1.1
FocusScope {
    id: root
    property var wallpaper: "file:///usr/local/QLauncher/background.jpg"
    Image {
            id: background
            fillMode: Image.PreserveAspectCrop
            smooth: true
            //horizontalAlignment: Image.AlignLeft
            verticalAlignment: Image.AlignTop
            source: wallpaper
            width: applicationWindow.width
	     height: applicationWindow.height
            sourceSize.width:applicationWindow.width
            sourceSize.height:applicationWindow.height
            onSourceChanged: {
                console.log("background changed.")
            }
            onStatusChanged: {
                 //console.log("Status changed to " + status);
                 if (status == Image.Error)
                 {
                    console.log("source: " + source + ": failed to load");
                    source = "qrc:/images/background";
                 }
              }
        }
    property int navbarMargin: QL.DisplayConfig.navBarVisible ? QL.DisplayConfig.navigationBarHeight : 0
    property int statusbarMargin: QL.DisplayConfig.statusBarHeight

    focus: true

    MouseArea {
        anchors.fill: parent
        onPressAndHold:
        {
            //console.debug("FocusScope onPressAndHold fileDialog.Open="+fileDialog.Open);
            fileDialog.close()
            fileDialog.open();
        }

    }


    FileDialog{
           id: fileDialog;
           title: "Please choose a file";
           //shortcuts: shortcuts.home;
           nameFilters: ["Image Files (*.jpg *.png *.gif)"];
           onAccepted: {
               background.source = (fileDialog.fileUrl.toString() !==""?fileDialog.fileUrl:wallpaper);
               QL.Launcher.pickWallpaper(fileDialog.fileUrl)
               //console.log("background changed:"+fileDialog.fileUrl)
               fileDialog.close()
           }
           visible: false
       }

    Keys.onPressed: {
         //console.debug("key onPressed:"+event.key);
              if (event.key === Qt.Key_PowerOff) {
                  QL.Launcher.powerControl()
                  //event.accepted = true;
              }
          }


    GridView {
        id: gridView

        anchors.fill: parent

        property int highlightedItem

        maximumFlickVelocity: height * 5

        header: Item {
            width: parent.width
            height: 80 * QL.DisplayConfig.dp
        }

        MouseArea {
            anchors.fill: parent
            propagateComposedEvents: true
            onPressAndHold:
            {
                //console.debug("GridView onPressAndHold");
                mouse.accepted = false
            }
            /*onClicked:
            {
                console.debug("GridView onClicked");
                 mouse.accepted = false
            }*/
        }


        add: Transition {
            NumberAnimation { properties: "opacity"; from: 0; to: 1; duration: 450 }
            NumberAnimation { property: "scale"; from: 0; to: 1.0; duration: 500 }
        }

        displaced: Transition {
            NumberAnimation { property: "opacity"; to: 1.0 }
            NumberAnimation { property: "scale"; to: 1.0 }
        }

        clip: true
        interactive: visible

        cellHeight: background.height / Config.Theme.getColumns()
        cellWidth: background.width / Config.Theme.getRows()

        model: app_model

        delegate: ApplicationTile {
            id: applicationTile

            height: GridView.view.cellHeight
            width: GridView.view.cellWidth

            source: "file:/usr/local/"+model.name+"/"+model.icon
            text: model.ui_name === "" ? model.name:model.ui_name

            onClicked:
            {
                applicationWindow.launchingAppIcon="file:/usr/local/"+model.name+"/"+model.icon
                applicationWindow.launchingAppName=model.ui_name === "" ? model.name:model.ui_name
                //console.debug("ThemeMain:onClicked "+model.name+",model.exitCallback="+model.exitCallback);
                QL.ApplicationManager.launchApplication(model.name,model.pkgName,model.ui_name,model.argv,model.exitCallback)
            }
            onPressAndHold: root.pressAndHold(model, x, y)

        }

        onHeightChanged: {
            if (height !== 0)
                cacheBuffer = Math.max(1080, height * 5)
        }
    }
}
