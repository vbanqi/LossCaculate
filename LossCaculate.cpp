
#include "LossCaculate.h"
#include "Utils.h"

namespace hola
{

LossCaculate::LossCaculate()
    : m_startIndex(0)
    , m_lastIndex(0)
    , m_recvCount(0)

    , m_packetLossCount(0)
    , m_lossPercent(0)
    , m_preTime(0)
    , m_reset(true)
{

}

LossCaculate::~LossCaculate()
{
}

void LossCaculate::Reset()
{
    ngx_memzero(m_packetBox, sizeof(m_packetBox));
}

void LossCaculate::AddCaculateSeq(uint16_t seq)
{
    uint16_t curSeq = (uint16_t)seq;
    if (m_preTime != 0) {
        if (SystemTimesMillis() - m_preTime > 2000 * 1000) {
            Reset();
        }
    }
    if (m_packetBox[curSeq % m_maxBoxLen] == curSeq) {
        return;//incomming duplicate packet
    }
    m_packetBox[curSeq % m_maxBoxLen] = curSeq;

    if (m_reset) {
        m_startIndex = curSeq;
        m_lastIndex = curSeq + 1;
        m_recvCount = 1;
        m_reset = false;
    }
    else {
        if (!Utils::IsMoreThan(curSeq , m_startIndex)) {
            m_startIndex = curSeq;
        }
        else if (Utils::IsMoreThan(curSeq, m_lastIndex)) {
            m_lastIndex = curSeq + 1;
        }
        m_recvCount ++;
    }
    m_preTime = SystemTimesMillis();

}

int LossCaculate::CaculatePersent()
{
    uint16_t expected_count = Utils::GetDistance(m_lastIndex, m_startIndex);
    uint16_t loss_count = expected_count - m_recvCount;
    HolaAssert(expected_count != 0);
    m_lossPercent = (int)loss_count * 256 / expected_count;
    m_packetLossCount += loss_count;
    m_reset = true;
    return m_lossPercent;
}

} // namespace PoseidonCore

