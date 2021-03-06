#include "Visualizer.hpp"
#include "./BubbleSort.hpp"
#include "./MergeSort.hpp"
#include "./SelectionSort.hpp"
#include "./QuickSort.hpp"


Visualizer::Visualizer(const std::string& configPath)
{
	m_config.setPath(configPath);
	m_config.parse();

	m_windowWidth = m_config.get("WINDOW_WIDTH");
	m_windowHeight = m_config.get("WINDOW_HEIGHT");
	m_marginTop = m_config.get("MARGIN_TOP");
	m_marginBetween = m_config.get("MARGIN_BETWEEN");
	m_sleepTime = m_config.get("ANIMATION_TIME_MS");

	m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "Visualization of sorting algorithms", sf::Style::Close);

	m_sortingAlgorithm = nullptr;
}

void Visualizer::start()
{
	if (!m_ui.setDefaultFont("consola.ttf"))
	{
		return;
	}

	m_sortingAlgorithm = std::make_unique<BubbleSort>(m_sleepTime);
	m_ui.setCurrentAlgorithm(m_sortingAlgorithm->getName());

	m_array.clear();

	int count = m_config.get("NUMBERS_COUNT");

	float sortableWidth = m_windowWidth / float(count) - m_marginBetween;
	for (unsigned i = 1; i <= count; i++)
	{
		Sortable sortable(i);
		sortable.setSize(sortableWidth, (i / float(count)) * (m_windowHeight - m_marginTop));

		m_array.push_back(sortable);
	}

	std::random_shuffle(m_array.begin(), m_array.end());

	mainLoop();
}

void Visualizer::mainLoop()
{
	while (m_window.isOpen())
	{
		handleEvents();
		update();
		render();
	}
}

void Visualizer::handleEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;

		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
			{
				if (!m_sortingAlgorithm->isRunning())
				{
					std::thread(&Visualizer::startSort, this).detach();
				}
				else
				{
					m_sortingAlgorithm->stop();
				}

				break;
			}

			case sf::Keyboard::R:
			{
				if (!m_sortingAlgorithm->isRunning())
				{
					std::random_shuffle(m_array.begin(), m_array.end());
				}

				break;
			}
			}

			break;
		}
		}
	}
}

void Visualizer::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		if (!m_sortingAlgorithm->isRunning())
		{
			m_sortingAlgorithm = std::make_unique<BubbleSort>(m_sleepTime);
			m_ui.setCurrentAlgorithm(m_sortingAlgorithm->getName());
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (!m_sortingAlgorithm->isRunning())
		{
			m_sortingAlgorithm = std::make_unique<SelectionSort>(m_sleepTime);
			m_ui.setCurrentAlgorithm(m_sortingAlgorithm->getName());
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		if (!m_sortingAlgorithm->isRunning())
		{
			m_sortingAlgorithm = std::make_unique<MergeSort>(m_sleepTime);
			m_ui.setCurrentAlgorithm(m_sortingAlgorithm->getName());
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		if (!m_sortingAlgorithm->isRunning())
		{
			m_sortingAlgorithm = std::make_unique<QuickSort>(m_sleepTime);
			m_ui.setCurrentAlgorithm(m_sortingAlgorithm->getName());
		}
	}

	m_ui.setComparisons(m_sortingAlgorithm->getComparisons());
	m_ui.setSwaps(m_sortingAlgorithm->getSwaps());
}

void Visualizer::render()
{
	m_window.clear();
	m_ui.render(m_window);

	float sortableWidth = m_windowWidth / (float)m_array.size();
	for (unsigned i = 0; i < m_array.size(); i++)
	{
		m_array[i].render(m_window, (i + 1)*sortableWidth - m_marginBetween);
	}

	m_window.display();
}

void Visualizer::startSort()
{
	m_sortingAlgorithm->start(m_array);
}