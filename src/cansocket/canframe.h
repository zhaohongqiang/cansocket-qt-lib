/****************************************************************************
* cansocket-qt.lib - Qt socketcan library
* Copyright (C) 2016 Georgije Bosiger <gbosiger@gmail.com>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#ifndef CANFRAME_H
#define CANFRAME_H

#include <QtCore/qshareddata.h>
#include <QtCore/qmetatype.h>

#include <cansocketglobal.h>

class CanFrame;
class CanFrameData;

#ifndef QT_NO_DATASTREAM
    CANSOCKET_EXPORT QDataStream &operator<<(QDataStream &, const CanFrame &);
    CANSOCKET_EXPORT QDataStream &operator>>(QDataStream &, CanFrame &);
#endif //QT_NO_DATASTREAM

#ifndef QT_NO_DEBUG_STREAM
    CANSOCKET_EXPORT QDebug operator<<(QDebug, const CanFrame &);
#endif //QT_NO_DEBUG_STREAM

class CANSOCKET_EXPORT CanFrame
{
    Q_GADGET
public:
    enum CanFrameType {
        DataFrame,
        FdFrame,
        ErrorFrame,
        RtrFrame,

        UnknownFrame = -1,
    };
    Q_ENUM(CanFrameType)

    enum CanFrameError {
        NoError = 0x000,
        TxTimeoutError = 0x001,
        LostArbitrationError = 0x002,
        ControllerProblemsError = 0x004,
        ProtocolViolationsError = 0x008,
        TransceiverStatusError = 0x010,
        NoAckOnTransmissionError = 0x020,
        BusOffError = 0x040,
        BusError = 0x080,
        ControllerRestartedError = 0x100,

        UnknownCanFrameError = 0x200,

        AllCanFrameErrors = 0x1FFFFFFF,
    };
    Q_FLAG(CanFrameError)
    Q_DECLARE_FLAGS(CanFrameErrors, CanFrameError)

    enum CanFrameFormat {
        StandardFrameFormat,
        ExtendedFrameFormat
    };
    Q_ENUM(CanFrameFormat)

    enum CanFrameIdMask {
        SffIdMask = 0x000007FF,
        EffIdMask = 0x1FFFFFFF
    };
    Q_ENUM(CanFrameIdMask)

    Q_DECLARE_FLAGS(CanFrameIdMasks, CanFrameIdMask)

    enum CanFrameIdFlag {
        EffIdFlag = 0x80000000,
        RtrIdFlag = 0x40000000,
        ErrorIdFlag = 0x20000000
    };
    Q_FLAG(CanFrameIdFlag)
    Q_DECLARE_FLAGS(CanFrameIdFlags, CanFrameIdFlag)

    enum CanFdFrameFlag {
        NoFdFrameFlag = 0x00,
        BitRateSwitchFlag = 0x01,
        ErrorStateIndicatorFlag = 0x02
    };
    Q_FLAG(CanFdFrameFlag)
    Q_DECLARE_FLAGS(CanFdFrameFlags, CanFdFrameFlag)

    CanFrame();
    CanFrame(CanFrameType type);
    CanFrame(const CanFrame &rhs);
    ~CanFrame();

    void swap(CanFrame &other);

    bool isValid() const;
    bool isEmpty() const;
    bool isNull() const;

    void clear();

    int maxDataLength() const;
    int maxDataTransferUnit() const;

    void setFrameType(CanFrameType frameType);
    CanFrameType frameType() const;

    bool isDataFrame() const;
    bool isFdFrame() const;
    bool isErrorFrame() const;
    bool isRtrFrame() const;

    void toDataFrame();
    void toFdFrame();
    void toErrorFrame();
    void toRtrFrame();

    bool operator ==(const CanFrame &rhs) const;
    bool operator !=(const CanFrame &rhs) const { return !operator==(rhs); }
    bool operator >(const CanFrame &rhs) const;
    bool operator <(const CanFrame &rhs) const;

    void setCanId(uint canId);
    uint canId() const;

    void setId(uint id);
    uint id() const;

    void setFrameFormat(CanFrameFormat format);
    CanFrameFormat frameFormat() const;

    bool setDataLength(int bytes);
    int dataLength() const;

    bool setFdFrameFlags(CanFdFrameFlags flags);
    CanFdFrameFlags fdFrameFlags() const;

    void setData(const char* data, int len = -1);

    char *data();
    const char *data() const;
    const char *constData() const { return data(); }

    const char &at(int i) const;
    const char &operator[](int i) const;
    char &operator[](int i);

    CanFrameErrors error() const;

protected:
    QSharedDataPointer<CanFrameData> d;

private:
    friend CANSOCKET_EXPORT QDataStream &operator<<(QDataStream &, const CanFrame &);
    friend CANSOCKET_EXPORT QDataStream &operator>>(QDataStream &, CanFrame &);
};
Q_DECLARE_SHARED(CanFrame)

Q_DECLARE_OPERATORS_FOR_FLAGS(CanFrame::CanFrameErrors)
Q_DECLARE_OPERATORS_FOR_FLAGS(CanFrame::CanFrameIdMasks)
Q_DECLARE_OPERATORS_FOR_FLAGS(CanFrame::CanFrameIdFlags)
Q_DECLARE_OPERATORS_FOR_FLAGS(CanFrame::CanFdFrameFlags)

Q_DECLARE_METATYPE(CanFrame)
Q_DECLARE_METATYPE(CanFrame::CanFrameErrors)

#endif // CANFRAME_H
