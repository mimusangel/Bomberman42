#ifndef BE_CORE_WINDOW_HPP
#define BE_CORE_WINDOW_HPP 1

/*!
 * \file Window.hpp
 * \brief Fenetre unique ou la partie graphique du moteur se deroule
 * \author mgallo, jblondea
 */

#include "Core.hpp"

/*! \namespace BeerEngine
 * espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
	/*! \class Window
	* \brief classe representant la fenetre du moteur
	*/
	class Window
	{
	private:
		std::string     _title; /*!< Titre de la fenetre*/
		int             _width; /*!< Largeur de la fenetre*/
		int             _height; /*!< Hauteur de la fenetre*/
		int				_xPos;
		int 			_yPos;
		int 			_windowWidth;
		int 			_windowHeight;
		GLFWwindow      *_window; /*!< Context GLFW de la fenetre*/
		glm::mat4       _perspective; /*!< Matrice de Perspective pour les rendu 3D*/
		glm::mat4       _ortho; /*!< Matrice Orthographique pour les rendu 2D*/
		bool			_close; /*!< Variable de requete pour la fermeture de la fenetre*/
		/*!
		*  \brief Constructeur
		*  Constructeur de la classe Window
		*  \param title : titre initiale de la fenetre
		*  \param width : largeur initiale de la fenetre
		*  \param height : hauteur initiale de la fenetre
		*/
		Window(std::string title, int width, int height);

		/*!
		*  \brief Copy Constructor
		*  Default copy constructor
		*/
		Window(const Window &val);

		/*!
		*  \brief Assignment operator
		*  Default assignment operator
		*/
		Window &operator=(const Window &val);

		static Window	*_Instance; /*!< Instance unique de la fenetre*/
	public:

		/*!
		*  \brief Constructor
		*  Default Constructor
		*/
		Window();

		/*!
		*  \brief Destructeur
		*  Destructeur de la classe Window
		*/
		~Window();
		/*!
		*  \brief recuperer les contexts GLFW
		*  Methode qui permet de recuperer le context GLFW de la fenetre
		*  \return context GLFW
		*/
		GLFWwindow      *getWindow(void);
		int     		*getXPos(void);
		int     		*getYPos(void);
		int				getWidth();
		int				getHeight();
		int				getWindowedWidth();
		int				getWindowedHeight();
		bool			isFullScreen();
		void			setWindowProperties(int x, int y, int width, int height);
		/*!
		*  \brief appel du nettoyage du rendu
		*  Methode qui permet de nettoyer le rendu de la fenetre
		*/
		void            clear(void);
		/*!
		*  \brief mise a jour des evenements
		*  Methode qui permet de mettre a jour les evenements de la fenetre telle que les inputs.
		*/
		void            update(void);
		/*!
		*  \brief changement de buffer
		*  Methode qui permet de changer de buffer graphique pour l'optimisation du rendu
		*/
		void            swapBuffer(void);
		/*!
		*  \brief recupere la projection 3d
		*  Methode qui permet de recuperer la matrice de perspective pour les rendu 3D
		*  \return matrice 4 x 4
		*/
		glm::mat4       &getProjection3D(void);
		/*!
		*  \brief recupere la projection 2d
		*  Methode qui permet de recuperer la matrice de orthographique pour les rendu 2D
		*  \return matrice 4 x 4
		*/
		glm::mat4       &getProjection2D(void);
		/*!
		*  \brief requete de fermeture
		*  Methode qui permet de demander au programme de se fermer.
		*/
		void			closeRequest(void);
		/*!
		*  \brief status de la fenetre
		*  Methode qui permet de savoir si la fenetre est fermer
		*  \return true, si la fenetre est femer et false si elle est ouverte
		*/
		bool			isClose(void);
		void			setFullScreen(void);
		void			setWindowed(void);
		void			resize(int width, int height);
		/*!
		*  \brief creer la fenetre
		*  Methode qui permet de creer la fenetre et de la recuperer.
		*  \return la fenetre
		*/
		static Window   *CreateWindow(std::string title, int width, int height);
		/*!
		*  \brief recuperer la fenetre
		*  Methode qui permet de recuperer la fenetre.
		*  \return la fenetre
		*/
		static Window	*GetInstance(void);

		static void CallbackResize(GLFWwindow* window, int cx, int cy);

	};
}

#endif