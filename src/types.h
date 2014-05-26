/*
    Copyright (C) 2014 Ales Katona.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TYPES_H
#define TYPES_H

#include <QObject>
#include <QString>
#include <QMap>

namespace Lighthouse {

    typedef QList<int> IntList;
    typedef QList<pid_t> PIDList;
    typedef QVector<unsigned long long> QLLVector;
    typedef QMap<QString, QString> AppNameMap;

    class ProcInfo
    {
    public:
        ProcInfo();
        void updateStat(QString& stat, unsigned long long totalTicks);
        void updateMemory(QString& mem, unsigned long totalMemory);
        void updateApplicationName(QString& appName);
        void updateName(QString& appName);

        const QString& getName() const;
        pid_t getPID() const;
        int getCPUUsage() const;
        int getMemoryUsage() const;
        int getNameState() const;
        bool isApplication() const;

        bool operator ==(const ProcInfo& other) const;
    private:
        QString fApplicationName;
        QString fStatName;
        QString fShowName;
        pid_t fPID;
        int fCPUUsage;
        int fMemoryUsage;
        QString fState;
        int fNameState;
        unsigned long fVmSize;
        unsigned long fVmRSS;
        unsigned long fSharedMem;
        unsigned long fSysTime;
        unsigned long fUserTime;
        unsigned long fTotalTicks;

        void setShowName(QString& source, int nameState);
    };

    typedef QMap<pid_t, ProcInfo> ProcMap;

    QString getUptimeString(qreal uptime);

    class BaseComparer {
    protected:
        BaseComparer(const ProcMap& procMap);
        const ProcMap& fProcMap;
    public:
        virtual bool operator()(const pid_t a, const pid_t b) const { return (a > b); }
    };

    class CPUComparer : public BaseComparer
    {
    public:
        CPUComparer(const ProcMap& procMap) : BaseComparer(procMap) {}
        bool operator()(const pid_t a, const pid_t b) const;
    };

    class MemoryComparer : public BaseComparer
    {
    public:
        MemoryComparer(const ProcMap& procMap) : BaseComparer(procMap) {}
        bool operator()(const pid_t a, const pid_t b) const;
    };

    class NameComparer : public BaseComparer
    {
    public:
        NameComparer(const ProcMap& procMap) : BaseComparer(procMap) {}
        bool operator()(const pid_t a, const pid_t b) const;
    };

}

#endif // TYPES_H
