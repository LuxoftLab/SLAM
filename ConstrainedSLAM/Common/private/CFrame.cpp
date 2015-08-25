#include <Common/CFrame.hpp>

CFrame::CFrame(IPointTracker::tPointTracks & tracks) : mTracks(tracks) {

}

CFrame::~CFrame() {
    std::cout << "destructor" << "\n";
    for(auto it = points.begin(); it != points.end(); it++) {
        PointTrack & track = mTracks[it->first];
        if(track.points.size() == 1) {
            std::cout << "delete track: " << it->first << std::endl;
            mTracks.erase(it->first);
        } else {
            track.points.pop_front();
        }
    }
}
