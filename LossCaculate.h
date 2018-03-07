#ifndef __POSEIDONCORE_PACKET_LOSS_CACULATE_H_INCLUDED__
#define __POSEIDONCORE_PACKET_LOSS_CACULATE_H_INCLUDED__

namespace hola
{

class LossCaculate
{
public:
	LossCaculate();
	~LossCaculate();

    void Reset();

    void AddCaculateSeq(uint16_t seq);
    int CaculatePersent();

    size_t MaxSequence() { return m_lastIndex - 1; }
    size_t LossCount() { return m_packetLossCount; }
private:
    static const size_t m_maxPacketLoss = 128;
    static const size_t m_maxBoxLen = 10;


    uint16_t m_startIndex;
    uint16_t m_lastIndex;
    uint32_t m_recvCount;

    int m_packetLossCount;
    int m_lossPercent;
    ngx_msec_t m_preTime;

    int m_packetBox[m_maxBoxLen] = {-1};
    bool m_reset;
}; // class LossCaculate

} // namespace PoseidonCore

#endif // ifndef __POSEIDONCORE_PACKET_LOSS_CACULATE_H_INCLUDED__

