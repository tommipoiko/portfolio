import sys
from menuwindow import MenuWindow
from PySide6.QtWidgets import QApplication


if __name__ == "__main__":

    app = QApplication(sys.argv)
    menuwindow = MenuWindow()
    menuwindow.resize(300, 400)
    menuwindow.show()
    app.exec()
