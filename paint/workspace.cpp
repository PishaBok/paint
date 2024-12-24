#include <paint/workspace.hpp>

WorkSpace::WorkSpace(QFrame* parent)
    : QFrame(parent), _strategy{nullptr}
{
    setObjectName("workSpace");
    setFocusPolicy(Qt::ClickFocus);
}

void WorkSpace::setStrategy(std::unique_ptr<WorkSpaceStrategy> strategy)
{
    _strategy = std::move(strategy);
}

void WorkSpace::addShape(std::unique_ptr<BaseShape> shape)
{
    _shapes.push_back(std::move(shape));
}

void WorkSpace::removeShape(BaseShape* shapeToRemove)
{
    auto it = std::find_if(_shapes.begin(), _shapes.end(),
        [shapeToRemove](const std::unique_ptr<BaseShape>& shape) {
            return shape.get() == shapeToRemove;
    });

    if (it != _shapes.end()) {_shapes.erase(it);}
}

void WorkSpace::addBound(std::unique_ptr<BoundLine> bound)
{
    _bounds.push_back(std::move(bound));
}

void WorkSpace::removeBoundsIf(const std::function<bool(const std::unique_ptr<BoundLine>&)>& predicate)
{
    _bounds.erase(std::remove_if(_bounds.begin(), _bounds.end(), predicate), _bounds.end());
}

const std::vector<std::unique_ptr<BaseShape>>& WorkSpace::shapes() const
{
    return _shapes;
}

const std::vector<std::unique_ptr<BoundLine>>& WorkSpace::bounds() const
{
    return _bounds;
}

void WorkSpace::loadFromFile(QFile& file)
{
    QDataStream in(&file);

    // 1. Проверка формата
    if (!validHeader(in)) 
    {
        QMessageBox::critical(nullptr, "Ошибка", "Неверный формат файла");
        return;
    }

    // 2. Чтение данных
    quint32 jsonSize;
    in >> jsonSize;
    QByteArray jsonBytes(jsonSize, Qt::Uninitialized);
    in.readRawData(jsonBytes.data(), jsonSize);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonBytes);
    fromJson(jsonDoc); // Загружаем данные из Json документа

    file.close();
    
    this->update();
}

void WorkSpace::saveToFile(QFile& file) const
{
    QDataStream out(&file);

    // 1. Заголовок
    out.writeRawData("PAINTDOC", 8);

    // 2. Json-данные
    QByteArray jsonBytes = toJson().toJson();
    out << quint32(jsonBytes.size());
    out.writeRawData(jsonBytes.data(), jsonBytes.size());

    file.close();
}







void WorkSpace::mousePressEvent(QMouseEvent* event)
{
    if (_strategy) {_strategy->mousePressEvent(event);}
}

void WorkSpace::mouseMoveEvent(QMouseEvent* event)
{
    if (_strategy) _strategy->mouseMoveEvent(event);
}

void WorkSpace::mouseReleaseEvent(QMouseEvent* event)
{
    if (_strategy) _strategy->mouseReleaseEvent(event);
}

void WorkSpace::keyPressEvent(QKeyEvent* event)
{
    if (_strategy) {_strategy->keyPressEvent(event);}
}

void WorkSpace::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);

    // Рисуем фигуры
    for (auto& shape: _shapes)
    {
        shape->draw(&painter);
    }

    // Рисуем связи
    for (auto& bound: _bounds)
    {
        bound->draw(&painter);
    }

    // Рисуем временную форму 
    if (_strategy) {_strategy->drawTemporary(&painter);} 
}


void WorkSpace::fromJson(const QJsonDocument& jsonDoc)
{
    _shapes.clear();
    _bounds.clear();

    QJsonObject wsJson = jsonDoc.object();

    // Загружаем фигуры
    for (const QJsonValue& shapeValue: wsJson["shapes"].toArray())
    {
        QJsonObject shapeObj = shapeValue.toObject();

        auto shape = shapeFactory.at(static_cast<ShapeType>(shapeObj["type"].toInt()))();
        shape->deserialize(shapeObj);

        _shapes.push_back(std::move(shape));
    }

    // Загружаем связи
    for (const QJsonValue& boundValue: wsJson["bounds"].toArray())
    {
        QJsonObject boundObj = boundValue.toObject();
        QJsonObject dataObj = boundObj["data"].toObject();

        auto startShape = findShapeById(dataObj["start"].toString());
        auto endShape = findShapeById(dataObj["end"].toString());
        if (!startShape || !endShape) {continue;} // Если хотябы одна из граничных фигур не найдена - связь не создается

        auto bound = std::make_unique<BoundLine>(startShape, endShape);
        bound->deserialize(boundObj);

        _bounds.push_back(std::move(bound));
    }
}

QJsonDocument WorkSpace::toJson() const
{
    QJsonObject wsJson;

    QJsonArray shapesArray;
    for (const auto& shape: _shapes)
    {
        shapesArray.append(shape->serialize());
    }

    QJsonArray boundsArray;
    for (const auto& bound: _bounds)
    {
        boundsArray.append(bound->serialize());
    }

    wsJson["shapes"] = shapesArray;
    wsJson["bounds"] = boundsArray;

    return QJsonDocument(wsJson);
}

bool WorkSpace::validHeader(QDataStream& fileData)
{
    char magic[8];
    fileData.readRawData(magic, 8);
    return (strncmp(magic, "PAINTDOC", 8) == 0);
}

BaseShape* WorkSpace::findShapeById(const QString& id) const
{
    auto it = std::find_if(_shapes.begin(), _shapes.end(), [&id](const std::unique_ptr<BaseShape>& shape)
    {
        return shape->id() == id; // Сравниваем id
    });

    return (it != _shapes.end()) ? it->get() : nullptr;
}

