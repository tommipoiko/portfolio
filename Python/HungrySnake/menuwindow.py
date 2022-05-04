from mainwindow import MainWindow
from PySide6.QtCore import Qt
from PySide6.QtWidgets import (QWidget, QPushButton, QLabel, QVBoxLayout)


class MenuWindow(QWidget):
    def __init__(self):
        QWidget.__init__(self)

        self.initMenu()

    # Initiating the separate components relevant to the menu
    def initMenu(self):
        self.startButton = QPushButton("Start playing")
        self.quitButton = QPushButton("Quit the game")
        self.text = QLabel("This is the menu")
        self.text.setAlignment(Qt.AlignCenter)
        self.layout = QVBoxLayout()
        self.layout.addWidget(self.text)
        self.layout.addWidget(self.startButton)
        self.layout.addWidget(self.quitButton)
        self.setLayout(self.layout)
        self.startButton.clicked.connect(self.startSlot)
        self.quitButton.clicked.connect(self.closeSlot)

    def initMainWindow(self):
        self.mainWindow = MainWindow()
        self.mainWindow.resize(300, 400)
        self.mainWindow.show()
        self.mainWindow.closed.connect(self.show)

    # Slots
    def startSlot(self):
        self.initMainWindow()
        self.hide()

    def closeSlot(self):
        self.mainWindow.close()
        self.close()
