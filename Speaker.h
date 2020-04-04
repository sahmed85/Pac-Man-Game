#include "mbed.h"
#include "pacman_music.h"



class Speaker : public PwmOut
{
public:
    enum BUZZY_Sounds {NO_SOUND, BEGIN, SIREN, CHOMP, EAT_GHOST, DEATH, EAT_FRUIT};
    
    Speaker(PinName nPin):PwmOut(nPin)
    {
       m_ulAudioArrayIndex = 0;
       SwitchSound(NO_SOUND);
    }
    
    void PlayNextValue()
    {
        if (m_pAudioArray != NULL)
        {
            write((float)m_pAudioArray[ GetNextValue() ]/255.0f);
        }       
    }
    
    void SwitchSound ( const BUZZY_Sounds &newSound)
    {
        if (newSound == m_enActiveAudioArray)
        {
            return;
        }
            
        m_ulAudioArrayIndex = 0;
        m_enActiveAudioArray = newSound;
        switch (newSound)
        {           
            case NO_SOUND:
                m_pAudioArray = NULL;
                break;   
            case BEGIN:
                m_pAudioArray = &data_BEGIN[0];
                break;   
            case CHOMP:
                 m_pAudioArray = &data_BEGIN[0];
                break;
            case EAT_GHOST:
                m_pAudioArray = &data_BEGIN[0];
                break;
            case DEATH:
                m_pAudioArray = &data_BEGIN[0];
                break;
            case EAT_FRUIT:
                m_pAudioArray = &data_BEGIN[0];
                break;              
            case SIREN:
            default:
                m_pAudioArray = &data_BEGIN[0];
                break; 
        }
                             
    }
    
    unsigned int GetNextValue()
    {
        m_ulAudioArrayIndex++;
        switch (m_enActiveAudioArray)
        {           
            case BEGIN:
                m_ulAudioArrayIndex %= NUM_BEGIN_ELEMENTS;
                break;   
            case CHOMP:
                 m_ulAudioArrayIndex %= NUM_BEGIN_ELEMENTS;
                break;
            case EAT_GHOST:
                 m_ulAudioArrayIndex %= NUM_BEGIN_ELEMENTS;
                break;
            case DEATH:
                 m_ulAudioArrayIndex %= NUM_BEGIN_ELEMENTS;
                 if (m_ulAudioArrayIndex == 0)
                 {
                     SwitchSound(BEGIN);
                 }
                break;
            case EAT_FRUIT:
                 m_ulAudioArrayIndex %= NUM_BEGIN_ELEMENTS;
                break;              
            case SIREN:
            default:
                 m_ulAudioArrayIndex %= NUM_BEGIN_ELEMENTS;
                break;          
        }
        return m_ulAudioArrayIndex;
    }
private:
    unsigned long m_ulAudioArrayIndex;
    BUZZY_Sounds m_enActiveAudioArray;
    const unsigned char *m_pAudioArray;
    
};
