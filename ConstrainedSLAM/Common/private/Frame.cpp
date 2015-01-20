#include <Common/Frame.h>

Frame::Frame(IPointTracker *tracker) : tracker(tracker) {

}

Frame::~Frame() {
    tracker->removeFrame(this);
}
