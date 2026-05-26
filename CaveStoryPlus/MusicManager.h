#pragma once
#include <string>

class SoundStream;
class MusicManager final
{
  public:
    enum class Track
    {
        none,
        cave,
        village,
        boss
    };

    MusicManager() = default;
    ~MusicManager();

    MusicManager(const MusicManager &) = delete;
    MusicManager(MusicManager &&) = default;
    MusicManager &operator=(const MusicManager &) = delete;
    MusicManager &operator=(MusicManager &&) = default;

    void Update();

    void SwitchTrack(Track track);

  private:
    SoundStream *m_pStream;

    static std::string GetTrackBeginPath(Track track);
    static std::string GetTrackLoopPath(Track track);

    Track m_ActiveTrack{Track::none};
    bool m_PlayingBegin{};
};
