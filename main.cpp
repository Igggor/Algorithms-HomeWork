#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>

class FileWriter {
private:
    std::string filename_;
    std::ofstream file_;
    std::vector<std::pair<std::string, std::string>> buffer_;
    
public:
    explicit FileWriter(const std::string& filename) : filename_(filename) {
        file_.open(filename_, std::ios::app);
        if (!file_.is_open())
            throw std::runtime_error("Cannot open file: " + filename_);
        std::cout << "File opened: " << filename_ << std::endl;
    }
    
    ~FileWriter() {
        flush();
        if (file_.is_open()) {
            file_.close();
            std::cout << "File closed: " << filename_ << std::endl;
        }
    }
    
    FileWriter(const FileWriter&) = delete;
    FileWriter& operator=(const FileWriter&) = delete;
    
    FileWriter(FileWriter&& other) noexcept : filename_(std::move(other.filename_)), file_(std::move(other.file_)), buffer_(std::move(other.buffer_)) {
        std::cout << "FileWriter moved: " << filename_ << std::endl;
    }
    
    FileWriter& operator=(FileWriter&& other) noexcept {
        if (this != &other) {
            flush();
            if (file_.is_open())
                file_.close();
            
            filename_ = std::move(other.filename_);
            file_ = std::move(other.file_);
            buffer_ = std::move(other.buffer_);
            
            std::cout << "FileWriter move assigned: " << filename_ << std::endl;
        }
        return *this;
    }
    
    void Add(const std::string& key, const std::string& value) {
        buffer_.emplace_back(key, value);
    }
    
    void flush() {
        if (!buffer_.empty() && file_.is_open()) {
            file_ << "{";
            for (size_t i = 0; i < buffer_.size(); ++i) {
                file_ << "\"" << buffer_[i].first << "\":\"" << buffer_[i].second << "\"";
                if (i < buffer_.size() - 1)
                    file_ << ",";
            }
            file_ << "}\n";
            file_.flush();
            buffer_.clear();
        }
    }
};

class Entity {
protected:
    std::shared_ptr<FileWriter> writer_;
    
public:
    explicit Entity(std::shared_ptr<FileWriter> writer) : writer_(std::move(writer)) {}
    
    virtual ~Entity() = default;
    
    Entity(Entity&& other) noexcept = default;
    Entity& operator=(Entity&& other) noexcept = default;
    
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;
    
    virtual void Add(const std::string& key, const std::string& value) {
        if (writer_)
            writer_->Add(key, value);
    }
    
    virtual void Flush() {
        if (writer_)
            writer_->flush();
    }
    
    std::shared_ptr<FileWriter> GetWriter() const {
        return writer_;
    }
};

/*
Тут я как пример реализовал несколько сущностей: пользователя, заказа и товаров. 
ПРосто чтобы на примере отработать
*/
class User : public Entity {
private:
    int id_;
    std::string name_;
    std::string email_;
    
public:
    User(int id, std::string name, std::string email, std::shared_ptr<FileWriter> writer)
        : Entity(std::move(writer)), id_(id), name_(std::move(name)), email_(std::move(email)) {}
    
    User(User&& other) noexcept = default;
    User& operator=(User&& other) noexcept = default;
    
    void SaveToFile() {
        Add("entity", "user");
        Add("id", std::to_string(id_));
        Add("name", name_);
        Add("email", email_);
        Flush();
        std::cout << "User " << id_ << " saved" << std::endl;
    }
};

class Order : public Entity {
private:
    int id_;
    int user_id_;
    double amount_;
    std::string status_;
    
public:
    Order(int id, int user_id, double amount, std::string status, std::shared_ptr<FileWriter> writer)
        : Entity(std::move(writer)), id_(id), user_id_(user_id), amount_(amount), status_(std::move(status)) {}
    
    Order(Order&& other) noexcept = default;
    Order& operator=(Order&& other) noexcept = default;
    
    void SaveToFile() {
        Add("entity", "order");
        Add("id", std::to_string(id_));
        Add("user_id", std::to_string(user_id_));
        Add("amount", std::to_string(amount_));
        Add("status", status_);
        Flush();
        std::cout << "Order " << id_ << " saved" << std::endl;
    }
};

class Product : public Entity {
private:
    int id_;
    std::string name_;
    double price_;
    int stock_;
    
public:
    Product(int id, std::string name, double price, int stock, std::shared_ptr<FileWriter> writer)
        : Entity(std::move(writer)), id_(id), name_(std::move(name)), price_(price), stock_(stock) {}
    
    Product(Product&& other) noexcept = default;
    Product& operator=(Product&& other) noexcept = default;
    
    void SaveToFile() {
        Add("entity", "product");
        Add("id", std::to_string(id_));
        Add("name", name_);
        Add("price", std::to_string(price_));
        Add("stock", std::to_string(stock_));
        Flush();
        std::cout << "Product " << id_ << " saved" << std::endl;
    }
};

class FileWriterFactory {
private:
    std::unordered_map<std::string, std::weak_ptr<FileWriter>> writers_;
    
public:
    std::shared_ptr<FileWriter> GetWriter(const std::string& filename) {
        auto it = writers_.find(filename);
        if (it != writers_.end()) {
            auto writer = it->second.lock();
            if (writer)
                return writer;
        }
        
        auto writer = std::make_shared<FileWriter>(filename);
        writers_[filename] = writer;
        return writer;
    }
    
    void Cleanup() {
        for (auto it = writers_.begin(); it != writers_.end();) {
            if (it->second.expired())
                it = writers_.erase(it);
            else 
                ++it;
        }
    }
};

int main() {
    try {
        FileWriterFactory factory;
        
        auto user_writer = factory.GetWriter("jsons/users.json");
        auto order_writer = factory.GetWriter("jsons/orders.json");
        auto product_writer = factory.GetWriter("jsons/products.json");
        
        std::cout << "\n=== Тест перемещения FileWriter ===\n";
        auto temp_writer = std::make_shared<FileWriter>("temp.json");
        auto moved_writer = std::move(temp_writer);
        
        std::cout << "\n=== Создание сущностей ===\n";
        std::vector<std::unique_ptr<Entity>> entities;
        
        entities.push_back(std::make_unique<User>(1, "Alice", "alice@example.com", user_writer));
        entities.push_back(std::make_unique<User>(2, "Bob", "bob@example.com", user_writer));
        entities.push_back(std::make_unique<Order>(1001, 1, 299.99, "pending", order_writer));
        entities.push_back(std::make_unique<Order>(1002, 2, 59.99, "shipped", order_writer));
        entities.push_back(std::make_unique<Product>(5001, "Laptop", 999.99, 10, product_writer));
        entities.push_back(std::make_unique<Product>(5002, "Mouse", 29.99, 50, product_writer));
        
        std::cout << "\n=== Сохранение данных ===\n";
        for (auto& entity : entities) {
            if (auto* user = dynamic_cast<User*>(entity.get()))
                user->SaveToFile(); 
            else if (auto* order = dynamic_cast<Order*>(entity.get()))
                order->SaveToFile();
            else if (auto* product = dynamic_cast<Product*>(entity.get()))
                product->SaveToFile();
        }
        
        std::cout << "\n=== Тест перемещения сущности ===\n";
        auto user3 = std::make_unique<User>(3, "Charlie", "charlie@example.com", user_writer);
        auto moved_user = std::move(user3);
        moved_user->SaveToFile();
        
        std::cout << "\n=== Повторное использование FileWriter ===\n";
        auto same_user_writer = factory.GetWriter("users.json");
        auto user4 = std::make_unique<User>(4, "David", "david@example.com", same_user_writer);
        user4->SaveToFile();
        
        factory.Cleanup();
        
    } 
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}