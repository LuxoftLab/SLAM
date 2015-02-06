#include <Common/Frame.h>

Frame::Frame(std::map<int, PointTrack> &tracks) : tracks(tracks) {

}

Frame::~Frame() {
    for(auto it = points.begin(); it != points.end(); it++) {
        PointTrack & track = tracks[it->first];
        if(track.points.size() == 1) {
            std::cout << "delete track: " << it->first << std::endl;
            tracks.erase(it->first);
        } else {
            track.points.pop_front();
        }
    }
}
