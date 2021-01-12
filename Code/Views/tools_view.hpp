/**
 * tools_view.hpp
 * Header of ToolsView class.
 */


#pragma once
#include "../simulator.hpp"
#include "../Components/button.hpp"
#include "../definitions.hpp"
#include "../Subjects/tools_subject.hpp"
#include "../Observers/simulation_observer.hpp"
#include "../Observers/creator_observer.hpp"
#include "../Helpers/viewport_calculator.hpp"


namespace zpr {

    /**
     * Class responsible for drawing create, delete, and save buttons, and handle actions from and to that buttons in the
     * right window of the main application window.
     */
    class ToolsView : public ToolsSubject, public SimulationObserver, public CreatorObserver{
	public:
		ToolsView(SimulatorDataRef data);
		void draw();
        bool isClicked(sf::Vector2i mouse_position);
        sf::View getView();
        void handleInput();
        void updateIsSimulating(bool is_simulating);
        void updateIsAddingCamera(bool is_adding_camera, int which_camera);

	private:
		void drawButtons();
        void resetButtons(int button_number_1, int button_number_2);
        void buttonInitializer();
		SimulatorDataRef data_;
		std::vector<Button> buttons_;
		sf::RectangleShape background_;
		sf::View toolsView_;
        bool isSimulating_, isAddingCameras_;
        ViewportCalculator viewportCalculator_;
	};

}
