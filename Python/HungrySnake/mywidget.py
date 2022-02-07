import random
from PySide6.QtCore import Qt
from PySide6.QtWidgets import (QWidget, QPushButton, QLabel, QVBoxLayout)


class MyWidget(QWidget):
    def __init__(self):
        QWidget.__init__(self)

        self.hello = ["Hallo welt!", "Ciao mondo!", "Hei maailma!",
                      "Hola mundo!", "Hei verden!"]

        self.button = QPushButton("Click me!")
        self.closeButton = QPushButton("Close me")

        self.text = QLabel("Hello World")
        self.text.setAlignment(Qt.AlignCenter)

        self.layout = QVBoxLayout()
        self.layout.addWidget(self.text)
        self.layout.addWidget(self.button)
        self.layout.addWidget(self.closeButton)
        self.setLayout(self.layout)

        self.button.clicked.connect(self.magic)
        self.closeButton.clicked.connect(self.close)

    def magic(self):
        self.text.setText(random.choice(self.hello))
