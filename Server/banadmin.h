#ifndef BANADMIN_H
#define BANADMIN_H

#include <QObject>
#include <QHostAddress> // IP
#include <fstream>
#include <../third_party/nlohmann/json/single_include/nlohmann/json.hpp>

/*!
 * \brief The BanAdmin class
 * No sabia que nombre ponerle Xd
 * \brief El funcionamiento es basico:
 *        Al instanciarlo, se interpreta el JSON y se guarda en una lista.
 *        El JSON se actualiza al destruirse el objeto.
 */
class BanAdmin : public QObject
{
    Q_OBJECT
public:
    BanAdmin();

    ~BanAdmin();

    BanAdmin(BanAdmin&) = delete; // Disable COPY

    void addDireccion(const QHostAddress& _dir);

    bool checkDireccion(const QHostAddress& _dir);

    void removeDireccion(const QHostAddress& _dir);

    const QList<QHostAddress>& getList() const;
private:
    QList<QHostAddress> listaDirecciones;
    typedef std::ifstream ifstream;
    typedef std::ofstream ofstream;
    typedef nlohmann::json json;
};

#endif // BANADMIN_H
