#ifndef VIZ_H
#define VIZ_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "graph.h"
namespace GUI {
    class Viz : public sf::Drawable {
    public:

        Viz(const int &radius, const sf::Font &font);

        // checks collision between x,y around a radius with all shapes in s
        // returns -1 if no collision, index of shape if collision
        int checkNodeCollision(int x, int y, int new_radius);
        
        // adds a node to shapes and adj list using mouse click event and radius 
        void addNode(sf::Event e);
        
        // selects a node to be used as an edge on mouse click, stores coords of click and index of node
        void selectNode(sf::Event e);
        
        // adds an edge using the selected nodes, resets selection
        void addLine();
        
        // sets the node that collides with the current mouse position to the start node if not set
        // if start node is set, then the colliding node will be set as the goal node
        // if both are set, no action is taken
        void setStartGoalNode(const sf::RenderWindow &window);
        
        // runs a graph search algorithm on the adj list, stores path and steps of exploration in arguments
        void runSearch(std::vector<std::vector<int>> (Graph::*search_path)(const int&, const int&)const);

        // 
        void updateExploredShapes(const int &update_rate);

        void updateClock(const double &dt);

        std::vector<sf::CircleShape*> getNodes();

        std::vector<sf::VertexArray> getEdges();

        std::vector<std::vector<int>> getAdj();

        void resetSearch();

        void clearGraph();
        
        void clearEdges();
        
        void resetSGNodes();

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        // contains nodes (circles) to be drawn
        std::vector<sf::CircleShape*> m_nodes;
        std::vector<sf::Text> m_node_txt;
        
        // contains line objects to be drawn
        std::vector<sf::VertexArray> m_lines;
        std::vector<int> m_edge_weights;
        std::vector<sf::Text> m_edge_txt;
        std::vector<std::vector<int>> m_weight_adj;

        // x,y coords of points selected to be end points for an edge
        std::vector<sf::Vector2f> m_selected_line_coords;

        // node index of edge end points
        std::vector<int> m_selected_line_nodes;

        // adjacency list to be used for graph search
        std::vector<std::vector<int>> m_adj;
       
        // path found from graph search
        std::vector<int> m_path;

        // steps found from graph search
        std::vector<int> m_explore;
        
        int m_explore_idx = 0;
        int m_path_idx = 0;
        int m_start_node = -1;
        int m_goal_node = -1;
        int m_clock_cnt = 0;
        
        // radius of nodes
        int m_radius;
        bool m_can_edit = true;

        sf::Font m_font;
    };
}
#endif
