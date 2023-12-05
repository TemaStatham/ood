#include "CApplication.h"
#include "CChangeCoordinatesOfShapeState.h"
#include <typeinfo>

CApplication::CApplication(istream& input, ostream& output, sf::RenderWindow& window)
    : m_in(input),
    m_out(output),
    m_window(window)
{
    m_canvas = new CCanvas(window, m_in);
    m_toolbar = new CToolbar(window, new CChangeCoordinatesOfShapeState(), m_canvas, new CFileSaver(m_canvas));
}

CApplication* CApplication::m_instance = nullptr;

CApplication* CApplication::GetInstance(std::istream& input, std::ostream& output, sf::RenderWindow& window)
{
    if (m_instance == nullptr) {
        m_instance = new CApplication(input, output, window);
    }

    return m_instance;
}

void CApplication::Read()
{
    std::string typeOfFigureAsString;

    while (m_in >> typeOfFigureAsString)
    {
        try
        {
            m_canvas->CreateShape(typeOfFigureAsString);
            m_out << "The shape was saved successfully" << std::endl;
        }
        catch (const std::exception& e)
        {
            m_out << e.what() << std::endl;
            std::string garbage;
            getline(m_in, garbage);
        }
    }
}
void CApplication::Write()
{
    auto shapes = m_canvas->GetShapes();

    for (auto figure : shapes) {
        m_out << figure->ToString();
    }
}

void CApplication::Start()
{
    m_window.setVerticalSyncEnabled(true);

    Read();

    while (m_window.isOpen()) {
        sf::Event event;

        while (m_window.pollEvent(event))
        {
            HandleEvent(event);
        }
    }

    Write();
}

void CApplication::HandleEvent(sf::Event event)
{
    m_canvas->SetCursorPosition(sf::Mouse::getPosition(m_window));
    m_toolbar->SetCursorPosition(sf::Mouse::getPosition(m_window));

    switch (event.type)
    {
    case sf::Event::Closed:
        m_window.close();
        break;
    case sf::Event::MouseButtonPressed:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.key.code == sf::Mouse::Left)
                {
                    if (typeid(*m_toolbar->GetState()) == typeid(CChangeCoordinatesOfShapeState))
                    {
                        m_canvas->AddNewSelectedShape();
                    }
                }
            }
        }
        else {
            if (event.key.code == sf::Mouse::Left)
            {
                if (typeid(*m_toolbar->GetState()) == typeid(CChangeCoordinatesOfShapeState))
                {
                    m_canvas->SetChoose();
                }
                else if (typeid(*m_toolbar->GetState()) == typeid(CChangeOutlineThicknessState))
                {
                    //m_canvas->ChangeOutlineThickness(m_toolbar->GetSelectedThickness());
                    m_canvas->Accept(new CChangeOutlineThicknessVisitor(m_toolbar->GetSelectedThickness()));
                }
                else if (typeid(*m_toolbar->GetState()) == typeid(CChangeShapeColorState))
                {
                    //m_canvas->ChangeShapeColor(m_toolbar->GetSelectedColor());
                    m_canvas->Accept(new CChangeShapeColorVisitor(m_toolbar->GetSelectedColor()));
                }
                else if (typeid(*m_toolbar->GetState()) == typeid(CChangeShapeOutlineColorState))
                {
                    //m_canvas->ChangeShapeOutlineColor(m_toolbar->GetSelectedColor());
                    m_canvas->Accept(new CChangeShapeOutlineColorVisitor(m_toolbar->GetSelectedColor()));
                }

                if (m_toolbar->PressedToButton())
                {
                    m_canvas->ResetSelectedShapes();
                }
            }
            if (event.key.code == sf::Mouse::Right)
            {
                if (typeid(*m_toolbar->GetState()) == typeid(CChangeCoordinatesOfShapeState))
                {
                    m_canvas->DeleteSelectedShape();
                }
            }
        }

        break;
    case sf::Event::MouseButtonReleased:
        if (event.key.code == sf::Mouse::Left)
        {
            if (typeid(*m_toolbar->GetState()) == typeid(CChangeCoordinatesOfShapeState))
            {
                //удаление функции изменения координат
                m_canvas->ResetIndex();
            }
        }
        break;
    case sf::Event::KeyPressed:
        if (typeid(*m_toolbar->GetState()) == typeid(CChangeCoordinatesOfShapeState))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
                {
                    //группировка фигуры в одну
                    m_canvas->GroupShapes();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
                {
                    //разгруппиоровка фигуры
                    m_canvas->UngroupShapes();
                }
            }
        }
        break;
    default:
        break;
    }

    if (typeid(*m_toolbar->GetState()) == typeid(CChangeCoordinatesOfShapeState))
    {
        m_canvas->ChangeCoordinatesOfShape();
    }

    m_window.clear(sf::Color(128, 128, 128));

    m_canvas->Draw();
    m_toolbar->Draw();

    m_window.display();
}
