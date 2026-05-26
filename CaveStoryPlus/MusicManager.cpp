#include "pch.h"
#include "MusicManager.h"
#include "SoundStream.h"

#include <cassert>

void MusicManager::SwitchTrack(MusicManager::Track track)
{
    if (track == Track::none)
    {
        SoundStream::Stop();
    }
    else
    {
        if (m_pStream == nullptr || track != m_ActiveTrack)
        {
            SoundStream::Stop();

            const std::string beginPath{GetTrackBeginPath(track)};
            m_pStream = new SoundStream(beginPath);
            m_pStream->Play(false);
            m_PlayingBegin = true;
        }
    }
    m_ActiveTrack = track;
}

MusicManager::~MusicManager()
{
    delete m_pStream;
}

void MusicManager::Update()
{
    if (m_PlayingBegin && m_pStream != nullptr)
    {
        if (!m_pStream->IsPlaying())
        {
            m_PlayingBegin = false;
            const std::string loopPath{GetTrackLoopPath(m_ActiveTrack)};
            m_pStream = new SoundStream(loopPath);
            m_pStream->Play(true);
        }
    }
}

std::string MusicManager::GetTrackBeginPath(Track track)
{
    switch (track)
    {
    case Track::cave:
        return "vivi_intro.ogg";
    case Track::village:
        return "mura_intro.ogg";
    case Track::boss:
        return "ginsuke_intro.ogg";
    case Track::none:
        return "";
    }

    assert(0 && "Track not handled");
    return {};
}

std::string MusicManager::GetTrackLoopPath(Track track)
{
    switch (track)
    {
    case Track::cave:
        return "vivi_loop.ogg";
    case Track::village:
        return "mura_loop.ogg";
    case Track::boss:
        return "ginsuke_loop.ogg";
    case Track::none:
        return "";
    }

    assert(0 && "Track not handled");
    return {};
}
