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
    MusicManager &operator=(const MusicManager &) = delete;
    MusicManager(MusicManager &&) = delete;
    MusicManager &operator=(MusicManager &&) = delete;

    void Update();

    void SwitchTrack(Track track);

  private:
    static std::string GetTrackBeginPath(Track track);
    static std::string GetTrackLoopPath(Track track);

    SoundStream *m_pStream{};
    Track m_ActiveTrack{Track::none};
    bool m_PlayingBegin{};
};
