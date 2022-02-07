import random
from PySide6 import QtCore
from PySide6.QtCore import Qt
from PySide6.QtWidgets import (QWidget, QPushButton, QLabel, QVBoxLayout)


class MainWindow(QWidget):
    closed = QtCore.Signal()

    def __init__(self):
        QWidget.__init__(self)

        self.hello = ["Hallo welt!", "Ciao mondo!", "Hei maailma!",
                      "Hola mundo!", "Hei verden!"]

        self.initButton()
        self.initCloseButton()
        self.initText()
        self.initLayout()

    # Initiating all the components in the UI
    def initButton(self):
        self.button = QPushButton("Click me!")
        self.button.clicked.connect(self.magic)

    def initCloseButton(self):
        self.closeButton = QPushButton("Go to menu")
        self.closeButton.clicked.connect(self.close)

    def initText(self):
        self.text = QLabel("Hello World")
        self.text.setAlignment(Qt.AlignCenter)

    def initLayout(self):
        self.layout = QVBoxLayout()
        self.layout.addWidget(self.text)
        self.layout.addWidget(self.button)
        self.layout.addWidget(self.closeButton)
        self.setLayout(self.layout)

    # Signals
    def closeEvent(self, event):
        self.closed.emit()
        super().closeEvent(event)

    # Slots
    def magic(self):
        self.text.setText(random.choice(self.hello))
