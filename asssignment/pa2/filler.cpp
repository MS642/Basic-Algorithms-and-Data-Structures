/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace.
 *
 */

#include <vector>
#include <map>
using namespace std;
 /**
  * Performs a multi-point flood fill using breadth first search.
  *
  * @param config      FillerConfig struct to setup the fill
  * @return animation  object illustrating progression of flood fill algorithm
  */
animation filler::fillBFS(FillerConfig& config)
{
    return fill<Queue>(config);
}

/**
 * Performs a multi-point flood fill using depth first search.
 *
 * @param config      FillerConfig struct to setup the fill
 * @return animation  object illustrating progression of flood fill algorithm
 */
animation filler::fillDFS(FillerConfig &config)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill.
     */
    return fill<Stack>(config);
}

/**
 * Run a multi-point flood fill on an image
 *
 * @param  config     FillerConfig struct with data for flood fill of image
 * @return animation  object illustrating progression of flood fill algorithm
 */
template <template <class T> class OrderingStructure> animation filler::fill(FillerConfig &config)
{
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure.
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are
     *              within (or equal to) tolerance distance from the center,
     *              to the ordering structure, and
     *              mark them as processed.
     *        2.    if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
     *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        ** LEFT(-x), DOWN(+y), RIGHT(+x), UP(-y). IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.** To reiterate, when you are exploring (filling out)
     *        from a given pixel, you must first try to fill the pixel to
     *        it's LEFT, then the one DOWN from it, then to the RIGHT and
     *        finally UP. If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        Because we are doing a multi-point flood fill you will repeat the flood
     *        fill from several locations stored in the `centers` variable of FillerConfig
     *        struct. Initial fill points should be visited in the order they stored in the
     *        `centers` vector. If a pixel lies in the fill region of multiple start points,
     *        it should only be updated by the first fill. To repeat, pixels should only
     *        be modified the first time they are visited by the filler algorithm.
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     *
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and
     *        it will be the one we test against.
     *
     */
    //cout << "hello" << endl;
    int size = config.centers.size();
    animation output;
    output.addFrame(config.img);
    unsigned int width = config.img.width();
    unsigned int height = config.img.height();
    vector<vector<bool>> visitedPoints(width, vector<bool>(height, false));

    vector<int> queueComplete;
    vector<OrderingStructure<point>> queue(size);
    for (int i = 0; i < size; i++) {
        point newPoint;
        newPoint.c = config.centers[i];
        newPoint.x = newPoint.c.x;
        newPoint.y = newPoint.c.y;
        queue[i].add(newPoint);
    }

    int counter = 0;
    for (int i = 0; i < size; i++) {
        while (!queue[i].isEmpty()) {
            point applyChange = queue[i].remove();
            if (visitedPoints[applyChange.x][applyChange.y]) {
                continue;
            }
            counter++;
            colorPicker* picker = (config.pickers[i]);
            HSLAPixel* pixel = config.img.getPixel(applyChange.x, applyChange.y);
            *pixel = (*picker)(applyChange);
            if (counter % config.frameFreq == 0) {
                output.addFrame(config.img);
            }
            visitedPoints[applyChange.x][applyChange.y] = true;

            unsigned int x = applyChange.x;
            unsigned int y = applyChange.y;
            if (x > 0) {
                point west = applyChange;
                west.x--;
                if (config.img.getPixel(west.x, west.y)->dist(west.c.color) <= config.tolerance) {
                    queue[i].add(west);
                }
            }
            if (y < (height - 1)) {
                point south = applyChange;
                south.y++;
                if (config.img.getPixel(south.x, south.y)->dist(south.c.color) <= config.tolerance) {
                    queue[i].add(south);
                }
            }
            if (x < (width - 1)) {
                point east = applyChange;
                east.x++;
                if (config.img.getPixel(east.x, east.y)->dist(east.c.color) <= config.tolerance) {
                    queue[i].add(east);
                }
            }
            if (y > 0) {
                point north = applyChange;
                north.y--;
                if (config.img.getPixel(north.x, north.y)->dist(north.c.color) <= config.tolerance) {
                    queue[i].add(north);
                }
            }
        }
    }
    output.addFrame(config.img);
    return output;
}
