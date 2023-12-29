#pragma once

#include <QObject>
#include <mutex>
#include <QTimer>

class QCatGrayToolTip : public QObject
{
    Q_OBJECT
public:
    static QCatGrayToolTip* Instance() noexcept
    {

        if(_instance == nullptr)
        {
            std::unique_lock<std::mutex>lock(*m_pMutex);
            if(_instance == nullptr)
            {
                _instance = new QCatGrayToolTip;
            }
        }

        return _instance;
    }

    static void Delete( void ) noexcept
    {
        if(_instance != nullptr)
        {
            if(_instance->m_pTimer != nullptr)
            {
                if(_instance->m_pTimer->isActive())
                {
                    _instance->m_pTimer->stop();
                    delete _instance->m_pTimer;
                    _instance->m_pTimer = nullptr;
                }
            }
            if(m_pMutex != nullptr)
            {
                delete m_pMutex;
                m_pMutex = nullptr;
            }
            delete _instance;
            _instance = nullptr;
        }
    }

    void ShowToolTip(QString text, int sleep = 500);
    void HideToolTip();

private:
    QCatGrayToolTip();
    ~QCatGrayToolTip();

    void InitConnect();

private:
    static QCatGrayToolTip *_instance;
    static std::mutex* m_pMutex;
    QTimer *m_pTimer;
    QString m_sShowText;
};

