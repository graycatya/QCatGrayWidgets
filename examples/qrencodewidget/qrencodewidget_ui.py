# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/home/catgray/catgray/code/CatLearnQt/modules/QCatGrayWidgets/examples/qrencodewidget/qrencodewidget.ui'
#
# Created by: PyQt5 UI code generator 5.15.6
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_qrencodewidget(object):
    def setupUi(self, qrencodewidget):
        qrencodewidget.setObjectName("qrencodewidget")
        qrencodewidget.resize(800, 600)
        self.verticalLayout = QtWidgets.QVBoxLayout(qrencodewidget)
        self.verticalLayout.setObjectName("verticalLayout")
        self.lineEdit = QtWidgets.QLineEdit(qrencodewidget)
        self.lineEdit.setText("www.test.com")
        self.lineEdit.setObjectName("lineEdit")
        self.verticalLayout.addWidget(self.lineEdit)
        self.widget = QtWidgets.QWidget(qrencodewidget)
        self.widget.setObjectName("widget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.widget)
        self.horizontalLayout.setObjectName("horizontalLayout")
        spacerItem = QtWidgets.QSpacerItem(223, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem)
        self.QrenCodeLabel = QtWidgets.QLabel(self.widget)
        self.QrenCodeLabel.setMinimumSize(QtCore.QSize(300, 0))
        self.QrenCodeLabel.setText("")
        self.QrenCodeLabel.setObjectName("QrenCodeLabel")
        self.horizontalLayout.addWidget(self.QrenCodeLabel)
        spacerItem1 = QtWidgets.QSpacerItem(223, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem1)
        self.verticalLayout.addWidget(self.widget)

        self.retranslateUi(qrencodewidget)
        QtCore.QMetaObject.connectSlotsByName(qrencodewidget)

    def retranslateUi(self, qrencodewidget):
        _translate = QtCore.QCoreApplication.translate
        qrencodewidget.setWindowTitle(_translate("qrencodewidget", "qrencodewidget"))
