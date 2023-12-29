#include "QCatGrayGraphicsDrawingBoardObject.h"

QCatGrayGraphicsDrawingBoardObject::QCatGrayGraphicsDrawingBoardObject(QObject *parent)
    : QObject(parent)
{
    m_yDrawingState = NO_STATE;
    m_yLastDrawingState = NO_STATE;
}

QCatGrayGraphicsDrawingBoardObject::~QCatGrayGraphicsDrawingBoardObject()
{

}
