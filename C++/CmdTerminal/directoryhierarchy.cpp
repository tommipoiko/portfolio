
/*
 * COMP.CS.110 Programming 2: Autumn 2021
 * Project3: Directory structure
 * File: directoryhierarchy.cpp
 * Name: Tommi Poikolainen
 * Email: tommi.poikolainen@tuni.fi
 * Description: Directory hierarchy -class
 * Functions: Allows for the manipulation of the directories in the program.
 * Functions range from adding directories to finding multilevel paths all the
 * way to annihilating the datastructure.
 */
#include "directoryhierarchy.hh"

#include <algorithm>
#include <vector>
#include <string>
#include <map>

/*
 * Initiates the directories, forms a default directory for the root,
 * called home. Also introduces the attribute-pointer that shows
 * the current directory.
 */
DirectoryHierarchy::DirectoryHierarchy()
{
    home_ = new Directory{
            .id_ = "home",
            .timestamp_ = EMPTY,
            .size_ = NO_SIZE
    };
    current_dir_ = home_;
}

/*
 * Destroys the directories.
 */
DirectoryHierarchy::~DirectoryHierarchy()
{
    for (const auto& dir : getAll()) {
        delete dir;
    }
}

/*
 * Adds the directories to the system, also helps show which
 * directories are parentless.
 */
void DirectoryHierarchy::addNewDirectory(const std::string &id,
                                         const std::string &timestamp,
                                         int size,
                                         std::ostream &output)
{
    if (getPointer(id) != nullptr) {
        output << "Error. Directory already added.\n";
        return;
    }

    auto* directory = new Directory{
            .id_ = id,
            .timestamp_ = timestamp,
            .size_ = size
    };

    parentless_.push_back(directory);
}

/*
 * Adds relations to the directories.
 */
void DirectoryHierarchy::addRelation(const std::string &directory,
                                     const std::string &parent,
                                     std::ostream &output)
{
    Directory* parent_dir = (parent ==  EMPTY) ? home_ : getPointer(parent);
    Directory* sub_dir = getPointer(directory);

    if (sub_dir == nullptr) {
        output << "Error. " << directory << " not found.\n";
        return;
    } else if (parent_dir == nullptr) {
        output << "Error. " << parent << " not found.\n";
        return;
    }

    auto it = std::find(parentless_.begin(), parentless_.end(), sub_dir);
    if (it == parentless_.end()) {
        parentless_.erase(it);
    }

    parent_dir->subdirectories_.push_back(sub_dir);
    sub_dir->parent_ = parent_dir;
}

/*
 * Prints the path to the working directory.
 */
void DirectoryHierarchy::commandPrintWorkingDirectory(std::ostream &output) const
{
    std::vector<std::string> dirs;
    auto* to_be_added = current_dir_;

    while (to_be_added->parent_ != nullptr) {
        std::string add = to_be_added->id_;
        dirs.push_back(add);
        to_be_added = to_be_added->parent_;
    }

    std::reverse(dirs.begin(), dirs.end());

    std::string print = "/home";
    for (auto id : dirs) {
        print += "/" + id;
    }
    print += "\n";

    output << print;
}

/*
 * Lists all of the available subdirectories, into which
 * the user can enter.
 */
void DirectoryHierarchy::commandList(std::ostream &output) const
{
    std::vector<std::string> rows;
    for (auto dir : current_dir_->subdirectories_) {
        std::string to_add;
        to_add += dir->id_ + ", ";
        to_add += dir->timestamp_ + ", ";
        to_add += std::to_string(dir->size_) + "\n";
        rows.push_back(to_add);
    }
    sort(rows.begin(), rows.end());
    for (std::string row : rows) {
        output << row;
    }
}

/* Prints all of the subdirectories in addition to the disk usage
 * that they possess.
 */
void DirectoryHierarchy::commandDiskUsage(std::ostream &output) const
{
    std::vector<std::string> sizes_and_names;
    std::vector<Directory*> dirs_for_size;
    std::map<std::string, int> end_product;
    int sum_of_size;
    for (auto dir : current_dir_->subdirectories_) {
        sum_of_size = 0;
        dirs_for_size = getAll(dir);
        for (auto sub_dir : dirs_for_size) {
            sum_of_size += sub_dir->size_;
        }
        end_product.insert({dir->id_, sum_of_size});
    }
    for (auto subdir : end_product) {
        std::string to_add;
        to_add += std::to_string(subdir.second) + " /" + subdir.first + "\n";
        sizes_and_names.push_back(to_add);
    }
    for (std::string row : sizes_and_names) {
        output << row;
    }
}

/*
 * Changes the current_dir_ pointer to point to a new subdirectory under it.
 */
void DirectoryHierarchy::commandChangeDirectory(const std::string &id, std::ostream &output)
{
    for (auto* dir : current_dir_->subdirectories_) {
        if (dir->id_ == id) {
            current_dir_ = dir;
            return;
        }
    }

    if (id == "..") {
        if (current_dir_ != home_) {
            current_dir_ = current_dir_->parent_;
            return;
        } else {
            output << "Error. Already at the root.\n";
            return;
        }
    } else if (id == "~") {
        current_dir_ = home_;
        return;
    }

    output << "Error. " << id << " not found.\n";
    return;
}

/*
 * Finds all of the available subdirectories up to a decided level of n.
 */
void DirectoryHierarchy::commandFind(const std::string &id, const int n, std::ostream &output) const
{
    std::vector<Directory*> subs = current_dir_->subdirectories_;
    if (n < 1) {
        output << "Error. Level can't be less than 1.\n";
        return;
    }
    for (auto dir : subs) {
        if (dir->id_ == id) {
            int level = 0;
            std::string to_add;
            std::vector<Directory*> up_to_level;
            for (auto dir : subs) {
                if (dir->id_ == id) {
                    up_to_level = gettolevel(dir, level, n, id);
                }
            }

            std::map<std::string, std::string> rows;
            for (auto dir : up_to_level) {
                rows.insert({get_path(dir), get_path(dir)});
            }

            for (auto dir : rows) {
                output << dir.first;
            }
            return;
        }
    }
    output << "Error. " << id << " not found.\n";
    return;
}

void DirectoryHierarchy::commandAsOldAs(const std::string &id, std::ostream &output) const
{
    output << id;
}

void DirectoryHierarchy::commandGreatest(const std::string &id, std::ostream &output) const
{
    output << id;
}

void DirectoryHierarchy::commandSmallest(const std::string &id, std::ostream &output) const
{
    output << id;
}

/*
 * Method is used to get the pointer of a certain directory.
 */
Directory* DirectoryHierarchy::getPointer(const std::string &id) const
{
    auto* directory = getPointerRecursive(home_, id);
    if (directory != nullptr) {
        return directory;
    }

    for (const auto& dir : parentless_) {
        if (dir->id_ == id) {
            return dir;
        }
    }

    return nullptr;
}

/*
 * An assisting method for the aforementioned method.
 */
Directory* DirectoryHierarchy::getPointerRecursive(Directory *current, const std::string &id) const
{
    if (current->id_ == id) {
        return current;
    }

    for (const auto& subdir : current->subdirectories_) {
        auto* found_directory = getPointerRecursive(subdir, id);
        if (found_directory != nullptr) {
            return found_directory;
        }
    }

    return nullptr;
}

/*
 * Return all of the directories in use.
 */
std::vector<Directory *> DirectoryHierarchy::getAll(Directory* current) const
{
    if (current == nullptr) {
        current = home_;
    }

    std::vector<Directory*> all;

    for (const auto& sub_dir : current->subdirectories_) {
        auto sub_all = getAll(sub_dir);
        for (const auto& directory : sub_all) {
            all.push_back(directory);
        }
    }

    all.push_back(current);

    return all;
}

/*
 * Returns a vector of directories up to a certain decided level.
 */
std::vector<Directory *> DirectoryHierarchy::gettolevel(Directory* current, int level, int max, const std::string &id) const
{
    ++level;
    std::vector<Directory*> all;

    for (const auto& sub_dir : current->subdirectories_) {
        if (level <= max) {
            auto sub_all = gettolevel(sub_dir, level, max, id);
            for (const auto& directory : sub_all) {
                all.push_back(directory);
            }
        }
    }

    if (current->id_ != id) {
        all.push_back(current);
    }

    return all;
}

/*
 * Returns the path to a certain directory.
 */
std::string DirectoryHierarchy::get_path(Directory *dir) const
{
    auto* ptr = dir;
    std::vector<std::string> dirs;
    while (ptr != current_dir_) {
        dirs.push_back(ptr->id_);
        ptr = ptr->parent_;
    }

    std::reverse(dirs.begin(), dirs.end());

    std::string print;
    for (auto id : dirs) {
        print += id + "/";
    }
    print.pop_back();
    print += "\n";

    return print;
}
