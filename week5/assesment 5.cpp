#include <iostream>
#include <string>
using namespace std;

//  Patient Node bst with threaded
class PatientNode {
public:
    int patientId;
    string patientName;
    PatientNode* left;
    PatientNode* right;
    bool isThreaded;

    PatientNode(int id, string name) {
        patientId = id;
        patientName = name;
        left = nullptr;
        right = nullptr;
        isThreaded = false;
    }
};

//  Department node bst
class DepartmentNode {
public:
    string name;
    DepartmentNode* left;
    DepartmentNode* right;
    PatientNode* patientRoot;

    DepartmentNode(string deptName) {
        name = deptName;
        left = nullptr;
        right = nullptr;
        patientRoot = nullptr;
    }
};

class HospitalManagementSystem {
private:
    DepartmentNode* root;

    DepartmentNode* addDepartment(DepartmentNode* node, const string& deptName) {
        if (!node) return new DepartmentNode(deptName);
        if (deptName < node->name)
            node->left = addDepartment(node->left, deptName);
        else if (deptName > node->name)
            node->right = addDepartment(node->right, deptName);
        return node;
    }

    PatientNode* addPatient(PatientNode* root, int id, const string& name) {
        if (!root) return new PatientNode(id, name);
        if (id < root->patientId)
            root->left = addPatient(root->left, id, name);
        else if (id > root->patientId)
            root->right = addPatient(root->right, id, name);
        return root;
    }

    PatientNode* deletePatient(PatientNode* root, int id) {
        if (!root) return nullptr;
        if (id < root->patientId)
            root->left = deletePatient(root->left, id);
        else if (id > root->patientId)
            root->right = deletePatient(root->right, id);
        else {
            if (!root->left) {
                PatientNode* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                PatientNode* temp = root->left;
                delete root;
                return temp;
            } else {
                PatientNode* temp = root->right;
                while (temp->left) temp = temp->left;
                root->patientId = temp->patientId;
                root->patientName = temp->patientName;
                root->right = deletePatient(root->right, temp->patientId);
            }
        }
        return root;
    }

    void displayDepartments(DepartmentNode* node, int level = 0) const {
        if (!node) return;
        for (int i = 0; i < level; i++) cout << "  ";
        cout << node->name << endl;
        displayDepartments(node->left, level + 1);
        displayDepartments(node->right, level);
    }

    void displayPatientsInOrder(PatientNode* root) const {
        if (!root) return;
        displayPatientsInOrder(root->left);
        cout << "Patient ID: " << root->patientId << ", Name: " << root->patientName << endl;
        if (!root->isThreaded) displayPatientsInOrder(root->right);
    }

    void generatePatientReportsNonRecursive(PatientNode* root) const {
        PatientNode* current = root;
        while (current) {
            while (current->left) current = current->left;

            while (current) {
                cout << "Patient ID: " << current->patientId << ", Name: " << current->patientName << endl;
                if (current->isThreaded)
                    current = current->right;
                else {
                    current = current->right;
                    break;
                }
            }
        }
    }

public:
    HospitalManagementSystem() : root(nullptr) {}

    void addDepartment(const string& deptName) {
        root = addDepartment(root, deptName);
    }

    void addSubDepartment(const string& parentDept, const string& subDeptName) {
        DepartmentNode* parent = findDepartment(root, parentDept);
        if (parent) {
            parent->left = addDepartment(parent->left, subDeptName);
        } else {
            cout << "Parent department not found!" << endl;
        }
    }

    void displayDepartments() const {
        displayDepartments(root);
    }

    void addPatientToDepartment(const string& deptName, int id, const string& name) {
        DepartmentNode* dept = findDepartment(root, deptName);
        if (dept) {
            dept->patientRoot = addPatient(dept->patientRoot, id, name);
        } else {
            cout << "Department not found!" << endl;
        }
    }

    void deletePatientFromDepartment(const string& deptName, int id) {
        DepartmentNode* dept = findDepartment(root, deptName);
        if (dept) {
            cout<<"patient id no : "<<id<<endl;
            dept->patientRoot = deletePatient(dept->patientRoot, id);
        } else {
            cout << "Department not found!" << endl;
        }
    }

    void displayPatientsInDepartment(const string& deptName) const {
        DepartmentNode* dept = findDepartment(root, deptName);
        if (dept) {
            displayPatientsInOrder(dept->patientRoot);
        } else {
            cout << "Department not found!" << endl;
        }
    }

    void generatePatientReports(const string& deptName) const {
        DepartmentNode* dept = findDepartment(root, deptName);
        if (dept) {
            generatePatientReportsNonRecursive(dept->patientRoot);
        } else {
            cout << "Department not found!" << endl;
        }
    }

    DepartmentNode* findDepartment(DepartmentNode* node, const string& deptName) const {
        if (!node) return nullptr;
        if (deptName == node->name) return node;
        if (deptName < node->name)
            return findDepartment(node->left, deptName);
        return findDepartment(node->right, deptName);
    }
};

int main() {
    HospitalManagementSystem hospital;

    // Adding  departments
    hospital.addDepartment("Cardiology");
    hospital.addDepartment("Neurology");
    hospital.addDepartment("Oncology");
    hospital.addDepartment("Orthopedic");
    
    //Adding Sub-departments
    hospital.addSubDepartment("Cardiology", "Pediatric Cardiology");
    hospital.addSubDepartment("Cardiology", "animal Cardiology");
    hospital.addSubDepartment("Cardiology", "children Cardiology");
    hospital.addSubDepartment("Neurology", "children Neurology");
    hospital.addSubDepartment("Neurology", "Nervous Neurology");
    hospital.addSubDepartment("Neurology", "animal Neurology");
    hospital.addSubDepartment("Oncology", "animal oncoology");
    hospital.addSubDepartment("Oncology", "childern oncoology");
    hospital.addSubDepartment("Orthopedic", " Upper body");
    hospital.addSubDepartment("Orthopedic", " lower body");
    cout << "Department Hierarchy:" << endl;
    hospital.displayDepartments();
    cout<<endl;
    // Adding patient records
    hospital.addPatientToDepartment("Cardiology", 101, "Ram");
    hospital.addPatientToDepartment("Cardiology", 102, "sham");
    hospital.addPatientToDepartment("Cardiology", 104, "Bobmarly");
    hospital.addPatientToDepartment("Neurology", 108, "Charlie");
    hospital.addPatientToDepartment("Oncology", 10, "San");
    hospital.addPatientToDepartment("Orthopedic", 11, "Cherry");
    //Displaying patient records
    
    cout << "\n Patient Records:" << endl;
    hospital.displayPatientsInDepartment("Cardiology");
    hospital.displayPatientsInDepartment("Neurology");
    hospital.displayPatientsInDepartment("Oncology");
    hospital.displayPatientsInDepartment("Orthopedic");
    
    //Displaying patient reports
    cout << "\nPatient Reports Cardiology:" << endl;
    hospital.generatePatientReports("Cardiology");
    cout<<"\n Patients Reports Neurology branch:"<<endl;
    hospital.generatePatientReports("Neurology");
    cout<<"\n Patients Reports Oncology branch:"<<endl;
    hospital.generatePatientReports("Oncology");
    cout<<"\n Patients ReportsOrthopedic branch:"<<endl;
    hospital.generatePatientReports("Orthopedic");
    cout<<"\nPatients discharged"<<endl;
    
    //Discharging patent 
    
    hospital.deletePatientFromDepartment("Cardiology",104);
    cout << "\nCardiology Patient Records:" << endl;
    
    hospital.displayPatientsInDepartment("Cardiology");
    
    return 0;
}
