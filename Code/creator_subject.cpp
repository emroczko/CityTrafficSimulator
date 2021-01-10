/**
 * creator_subject.cpp
 * Implementation of CreatorSubject class.
 */


#include "creator_subject.hpp" 

namespace zpr {

    /**
     * Method which adds observers to vector.
     * @param observer - CreatorHandler class observer.
     */
	void CreatorSubject::add(std::shared_ptr<CreatorObserver> observer)
	{
		this->observers_.push_back(observer);
	}

    /**
     * Method which notifies observers about changed coordinates of currently chosen cell.
     * @param coords - New coordinates of cell.
     */
	void CreatorSubject::notifySelectedCell(sf::Vector2i coords)
	{
		for (std::shared_ptr<CreatorObserver> observer : this->observers_) {
			observer->updateSelectedCell(coords);
		}
	}

    /**
     * Method which notifies observers when vector of cells has changed.
     * @param cells - Vector of new cells.
     */
	void CreatorSubject::notifyCells(std::vector<Cell> cells)
	{
		for (std::shared_ptr<CreatorObserver> observer : this->observers_) {
			observer->updateCells(cells);
		}
	}
   
    /**
     * Method which notifies observers when user is drawing road or not.
     * @param is_drawing_road - True when user is drawing road.
     */
	void CreatorSubject::notifyIsDrawingRoad(bool is_drawing_road)
	{
		for (std::shared_ptr<CreatorObserver> observer : this->observers_) {
			observer->updateIsDrawingRoad(is_drawing_road);
		}
	}

    /**
     * Method which notifies observers when user is deleting road or not.
     * @param is_deleting_road - True when user is deleting road, false otherwise.
     */
    void CreatorSubject::notifyIsDeletingRoad(bool is_deleting_road)
    {
        for (std::shared_ptr<CreatorObserver> observer : this->observers_) {
            observer->updateIsDeletingRoad(is_deleting_road);
        }
    }

    /**
     * Method which notifies observers when user is adding camera or not.
     * @param is_adding_camera - True when user is adding camera, false otherwise.
     * @param which_camera - Being added camera's number.
     */
    void CreatorSubject::notifyIsAddingCamera(bool is_adding_camera, int which_camera)
    {
        for (std::shared_ptr<CreatorObserver> observer : this->observers_) {
            observer->updateIsAddingCamera(is_adding_camera, which_camera);
        }
    }
    
    /**
     * Method which notifies observers when user added the camera and where user placed it.
     * @param which_camera - Being added camera's number.
     * @param row - Row in which camera was placed.
     * @param col - Column in which camera was placed.
     */
	void CreatorSubject::notifyCameraAdded(int which_camera, int row, int col)
	{
		for (std::shared_ptr<CreatorObserver> observer : this->observers_) {
			observer->updateCameraAdded(which_camera, row, col);
		}
	}

    /**
     * Method which notifies observers when user is deleting certain camera.
     * @param which_camera - Deleted camera's number.
     */
    void CreatorSubject::notifyIsDeletingCamera(int which_camera)
    {
        for (std::shared_ptr<CreatorObserver> observer : this->observers_) {
            observer->updateIsDeletingCamera(which_camera);
        }
    }

    /**
     * Method which notifies observers when user is saving map to file.
     */
    void CreatorSubject::notifySave()
    {
        for (std::shared_ptr<CreatorObserver> observer : this->observers_) {
            observer->saveToFile();
        }
    }
    
}
