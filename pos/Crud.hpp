#ifndef __CRUD__HPP__
#define __CRUD__HPP__

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <cassert>

/**
 * @brief Clase abstracta que describe el comportamiento de crear, leer, actualizar y
 * eliminar de una estructura
 *
 */
template <typename K, typename T>
class Crud
{
public:
    Crud(const std::string &filename) : file(filename)
    {
        std::ifstream in(fileName(), std::ios::binary);
        if (in.is_open())
        {
            T data;
            std::streampos pos = in.tellg();
            while (in.read((char *)&data, sizeof(T)))
            {
                dict.insert(std::make_pair(data.id, pos));
                addData(data, pos);
                pos = in.tellg();
            }
        }
        else
        {
            std::ofstream out(fileName(), std::ios::binary | std::ios::app);
            assert(out.is_open());
        }
    }

    virtual ~Crud() {}

    /**
     * @brief Esta funcion debe ser sobrecargada en sus subclases con el nombre de fichero
     * donde se guardaran los registros
     *
     * @return const std::string& Nombre de fichero
     */
    const std::string &fileName() const { return file; }

    /**
     * @brief Guarda un nuevo registro y lo agrega al indice de fichero
     *
     * @param data Registro a guardar
     * @return true Si tiene exito
     * @return false Si falla, porque el id ya esta registrado
     */
    bool create(const T &data)
    {
        if (dict.find(data.id) != dict.end())
        {
            return false;
        }
        std::ofstream out(fileName(), std::ios::app | std::ios::binary | std::ios::ate | std::ios::in);
        assert(out.is_open());
        auto pos = out.tellp();
        if (addData(data, pos))
        {
            dict.insert(std::make_pair(data.id, pos));
            out.write((const char *)&data, sizeof(T));
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief Lee un registro del fichero de acuerdo con su identificador
     *
     * @param key Identificador único del registro
     * @param data En caso de tener éxito, guarda el registro leído
     * @return true Si tiene éxito
     * @return false Si el identificador no se encuentra en el indice
     */
    bool read(K key, T &data)
    {
        auto it = dict.find(key);
        if (it != dict.end())
        {
            std::ifstream in(fileName(), std::ios::binary);
            assert(in.is_open());
            in.seekg(it->second);
            in.read((char *)&data, sizeof(T));
            return true;
        }
        return false;
    }

    /**
     * @brief Lee una lista de registros que cumplen un determinado criterio
     *
     * @tparam Pred Functor o puntero a funcion
     * @param pred Criterio que deben cumplir los registros a seleccionar
     * @return std::vector<T> Lista de registros
     */
    template <typename Pred>
    std::vector<T> read(Pred pred)
    {
        std::ifstream in(fileName(), std::ios::binary);
        assert(in.is_open());
        T data;
        std::vector<T> result;
        while (in.read((char *)&data, sizeof(T)))
        {
            if (pred(data))
            {
                result.push_back(data);
            }
        }
    }

    /**
     * @brief Actualiza un registro de acuerdo a su identificador
     *
     * @param data Valor del nuevo registro actualizado
     * @return true Si tiene éxito
     * @return false Si el registro no se encuentra en el indice
     */
    bool update(const T &data)
    {
        auto it = dict.find(data.id);
        if (it != dict.end())
        {
            std::ofstream out(fileName(), std::ios::out | std::ios::in | std::ios::binary);
            assert(out.is_open());
            out.seekp(it->second);
            out.write((const char *)&data, sizeof(T));
            return true;
        }
        return false;
    }

    /**
     * @brief Elimina unu registro de acuerdo a su identificador
     *
     * @param key Identificador del registro a eliminar
     * @return true Si tiene éxito
     * @return false Si el registro no se encuentra en el indice
     */
    bool erase(K key)
    {
        return false;
    }

protected:
    virtual bool addData(const T &, std::streampos)
    {
        return true;
    }

private:
    std::string file;
    std::map<K, std::streampos> dict;
};

#endif