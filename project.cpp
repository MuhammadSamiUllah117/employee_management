#include <iostream>
#include <string>

const int MAX_EMPLOYEES = 100; // Maximum number of employees in a department

// Base class for Employee
class Employee {
protected:
    int employeeID;
    std::string name;
    std::string department;
    std::string role;

public:
    Employee(int id, std::string n, std::string dept, std::string r)
        : employeeID(id), name(n), department(dept), role(r) {}

    virtual ~Employee() {}

    // Getters
    int getEmployeeID() const { return employeeID; }
    std::string getName() const { return name; }
    std::string getDepartment() const { return department; }
    std::string getRole() const { return role; }

    // Setters
    void setName(const std::string& n) { name = n; }
    void setDepartment(const std::string& dept) { department = dept; }
    void setRole(const std::string& r) { role = r; }

    // Virtual function for performance evaluation
    virtual void evaluatePerformance() const {
        std::cout << "Performance evaluation for " << name << " is not implemented." << std::endl;
    }
};

// Derived class for FullTimeEmployee
class FullTimeEmployee : public Employee {
private:
    double annualSalary;

public:
    FullTimeEmployee(int id, std::string n, std::string dept, double salary)
        : Employee(id, n, dept, "Full-Time"), annualSalary(salary) {}

    // Getter
    double getAnnualSalary() const { return annualSalary; }

    // Setter
    void setAnnualSalary(double salary) { annualSalary = salary; }

    void evaluatePerformance() const override {
        std::cout << "Performance evaluation for Full-Time Employee " << name << " with salary: $" << annualSalary << std::endl;
    }
};

// Derived class for PartTimeEmployee
class PartTimeEmployee : public Employee {
private:
    double hourlyRate;
    int hoursWorked;

public:
    PartTimeEmployee(int id, std::string n, std::string dept, double rate, int hours)
        : Employee(id, n, dept, "Part-Time"), hourlyRate(rate), hoursWorked(hours) {}

    // Getters
    double getHourlyRate() const { return hourlyRate; }
    int getHoursWorked() const { return hoursWorked; }

    // Setters
    void setHourlyRate(double rate) { hourlyRate = rate; }
    void setHoursWorked(int hours) { hoursWorked = hours; }

    void evaluatePerformance() const override {
        std::cout << "Performance evaluation for Part-Time Employee " << name << " with hourly rate: $" << hourlyRate
                  << " and hours worked: " << hoursWorked << std::endl;
    }
};

// Department class to manage a list of employees
class Department {
private:
    std::string departmentName;
    Employee* employees[MAX_EMPLOYEES];
    int employeeCount;

public:
    Department(const std::string& name) : departmentName(name), employeeCount(0) {
        for (int i = 0; i < MAX_EMPLOYEES; ++i) {
            employees[i] = nullptr;
        }
    }

    void addEmployee(Employee* emp) {
        if (employeeCount < MAX_EMPLOYEES) {
            employees[employeeCount++] = emp;
        } else {
            std::cout << "Employee list is full." << std::endl;
        }
    }

    void removeEmployee(int employeeID) {
        for (int i = 0; i < employeeCount; ++i) {
            if (employees[i]->getEmployeeID() == employeeID) {
                delete employees[i];
                for (int j = i; j < employeeCount - 1; ++j) {
                    employees[j] = employees[j + 1];
                }
                employees[--employeeCount] = nullptr;
                return;
            }
        }
        std::cout << "Employee not found." << std::endl;
    }

    void listEmployees() const {
        for (int i = 0; i < employeeCount; ++i) {
            std::cout << "ID: " << employees[i]->getEmployeeID() << ", Name: " << employees[i]->getName() 
                      << ", Department: " << employees[i]->getDepartment() << ", Role: " << employees[i]->getRole() << std::endl;
        }
    }

    std::string getDepartmentName() const { return departmentName; }

    ~Department() {
        for (int i = 0; i < employeeCount; ++i) {
            delete employees[i];
        }
    }
};

// Function to create FullTimeEmployee
FullTimeEmployee* createFullTimeEmployee() {
    int id;
    std::string name;
    double salary;

    std::cout << "Enter Full-Time Employee ID: ";
    std::cin >> id;
    std::cin.ignore(); // To ignore the newline character left in the buffer
    std::cout << "Enter Full-Time Employee Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Annual Salary: ";
    std::cin >> salary;

    return new FullTimeEmployee(id, name, "Sales", salary); // Assuming "Sales" as department
}

// Function to create PartTimeEmployee
PartTimeEmployee* createPartTimeEmployee() {
    int id;
    std::string name;
    double rate;
    int hours;

    std::cout << "Enter Part-Time Employee ID: ";
    std::cin >> id;
    std::cin.ignore(); // To ignore the newline character left in the buffer
    std::cout << "Enter Part-Time Employee Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Hourly Rate: ";
    std::cin >> rate;
    std::cout << "Enter Hours Worked: ";
    std::cin >> hours;

    return new PartTimeEmployee(id, name, "Sales", rate, hours); // Assuming "Sales" as department
}

// Main function
int main() {
    Department sales("Sales");

    int choice;
    do {
        std::cout << "\nEmployee Management System\n";
        std::cout << "1. Add Full-Time Employee\n";
        std::cout << "2. Add Part-Time Employee\n";
        std::cout << "3. List Employees\n";
        std::cout << "4. Remove Employee\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            Employee* emp = createFullTimeEmployee();
            sales.addEmployee(emp);

        } else if (choice == 2) {
            Employee* emp = createPartTimeEmployee();
            sales.addEmployee(emp);

        } else if (choice == 3) {
            std::cout << "\nEmployee List:" << std::endl;
            sales.listEmployees();

        } else if (choice == 4) {
            int id;
            std::cout << "Enter Employee ID to remove: ";
            std::cin >> id;
            sales.removeEmployee(id);

        } else if (choice != 5) {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

    } while (choice != 5);

    return 0;
}
