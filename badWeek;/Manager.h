#include <SFML/Graphics/Texture.hpp>

#include <unordered_map>
#include <string>
#include <memory>

template <typename T>
class Manager {
	public:
		static std::shared_ptr<T> carregar(const std::string& chave) {
			auto recurso = recursos.find(chave);

			if (recurso != recursos.end())
				return recurso->second;
			else {
				std::shared_ptr<T> temp = std::make_shared<T>();
				temp->loadFromFile(chave);

				recursos.insert({ chave, temp });
				return temp;
			}
		}
	private:
		static std::unordered_map<std::string, std::shared_ptr<T>> recursos;
};

template <typename T>
std::unordered_map<std::string, std::shared_ptr<T>> Manager<T>::recursos;

typedef Manager<sf::Texture> TextureManager;