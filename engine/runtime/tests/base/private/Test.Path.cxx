#include <catch2/catch.hpp>
#include <GxBase/Storage/Path.hxx>


TEST_CASE("Path appending")
{
    using namespace Graphyte::Storage;

    std::string path{};
    CHECK(path == "");

    AppendPath(path, "root");
    CHECK(path == "root");

    AppendPath(path, "game");
    CHECK(path == "root/game");

    AppendPath(path, "assets");
    CHECK(path == "root/game/assets");

    AppendPath(path, "meshes");
    CHECK(path == "root/game/assets/meshes");

    AppendPath(path, "package");
    CHECK(path == "root/game/assets/meshes/package");

    AppendPath(path, "main.mesh");
    CHECK(path == "root/game/assets/meshes/package/main.mesh");

    AppendPath(path, "");
    CHECK(path == "root/game/assets/meshes/package/main.mesh");

    AppendPath(path, "");
    CHECK(path == "root/game/assets/meshes/package/main.mesh");

    AppendPath(path, "");
    CHECK(path == "root/game/assets/meshes/package/main.mesh");

    AppendPath(path, "subname/after/filename.html");
    CHECK(path == "root/game/assets/meshes/package/main.mesh/subname/after/filename.html");
}

TEST_CASE("Path appending - denegerated cases")
{
    using namespace Graphyte::Storage;

    std::string result{ "app.demo" };

    AppendPath(result, "../../");
    CHECK(result == "app.demo/../../");

    REQUIRE(CanonicalizePath(result));
    REQUIRE(result == "app.demo/..");
}

TEST_CASE("Path combining")
{
    using namespace Graphyte::Storage;

    CHECK(CombinePath("root", "game") == "root/game");
    CHECK(CombinePath("root", "game", "assets") == "root/game/assets");
    CHECK(CombinePath("root", "game", "assets", "meshes") == "root/game/assets/meshes");
    CHECK(CombinePath("root", "game", "assets", "meshes", "package") == "root/game/assets/meshes/package");
    CHECK(CombinePath("root", "game", "assets", "meshes", "package", "main.mesh") == "root/game/assets/meshes/package/main.mesh");
}

TEST_CASE("Changing extension - empty path")
{
    using namespace Graphyte::Storage;

    std::string path = "";

    ChangeExtension(path, ".txt");
    CHECK(path == ".txt");

    ChangeExtension(path, ".ref");
    CHECK(path == ".ref");

    ChangeExtension(path, "");
    CHECK(path == "");

    ChangeExtension(path, "txt");
    CHECK(path == ".txt");

    ChangeExtension(path, "wtf");
    CHECK(path == ".wtf");
}

TEST_CASE("Changing extension - simple filename path")
{
    using namespace Graphyte::Storage;

    std::string path = "file";

    ChangeExtension(path, ".txt");
    CHECK(path == "file.txt");

    ChangeExtension(path, ".ref");
    CHECK(path == "file.ref");

    ChangeExtension(path, "");
    CHECK(path == "file");

    ChangeExtension(path, "txt");
    CHECK(path == "file.txt");

    ChangeExtension(path, "wtf");
    CHECK(path == "file.wtf");
}

TEST_CASE("Changing extension - simple filename path with base path")
{
    using namespace Graphyte::Storage;

    std::string path = "some/path/to/file";

    ChangeExtension(path, ".txt");
    CHECK(path == "some/path/to/file.txt");

    ChangeExtension(path, ".ref");
    CHECK(path == "some/path/to/file.ref");

    ChangeExtension(path, "");
    CHECK(path == "some/path/to/file");

    ChangeExtension(path, "txt");
    CHECK(path == "some/path/to/file.txt");

    ChangeExtension(path, "wtf");
    CHECK(path == "some/path/to/file.wtf");
}

TEST_CASE("Changing extension - simple filename + extension path with base path")
{
    using namespace Graphyte::Storage;

    std::string path = "some/path/to/file.cxx";

    ChangeExtension(path, ".txt");
    CHECK(path == "some/path/to/file.txt");

    ChangeExtension(path, ".ref");
    CHECK(path == "some/path/to/file.ref");

    ChangeExtension(path, "");
    CHECK(path == "some/path/to/file");

    ChangeExtension(path, "txt");
    CHECK(path == "some/path/to/file.txt");

    ChangeExtension(path, "wtf");
    CHECK(path == "some/path/to/file.wtf");
}

TEST_CASE("Changing file name - empty path")
{
    using namespace Graphyte::Storage;

    std::string path = "";

    ChangeFilename(path, "file.txt");
    CHECK(path == "file.txt");

    ChangeFilename(path, "file");
    CHECK(path == "file");

    ChangeFilename(path, "");
    CHECK(path == "");

    ChangeFilename(path, "other-file.doc");
    CHECK(path == "other-file.doc");
}

TEST_CASE("Changing file name - just file name")
{
    using namespace Graphyte::Storage;

    std::string path = "main";

    ChangeFilename(path, "file.txt");
    CHECK(path == "file.txt");

    ChangeFilename(path, "file");
    CHECK(path == "file");

    ChangeFilename(path, "");
    CHECK(path == "");

    ChangeFilename(path, "other-file.doc");
    CHECK(path == "other-file.doc");
}

TEST_CASE("Changing file name - just file name with extension")
{
    using namespace Graphyte::Storage;

    std::string path = "main";

    ChangeFilename(path, "file.txt");
    CHECK(path == "file.txt");

    ChangeFilename(path, "file");
    CHECK(path == "file");

    ChangeFilename(path, "");
    CHECK(path == "");

    ChangeFilename(path, "other-file.doc");
    CHECK(path == "other-file.doc");
}

TEST_CASE("Changing file name - just path")
{
    using namespace Graphyte::Storage;

    std::string path = "path/to/file/";

    ChangeFilename(path, "file.txt");
    CHECK(path == "path/to/file/file.txt");

    ChangeFilename(path, "file");
    CHECK(path == "path/to/file/file");

    ChangeFilename(path, "");
    CHECK(path == "path/to/file/");

    ChangeFilename(path, "other-file.doc");
    CHECK(path == "path/to/file/other-file.doc");
}

TEST_CASE("Changing file name - path with file name")
{
    using namespace Graphyte::Storage;

    std::string path = "path/to/file/other.html";

    ChangeFilename(path, "file.txt");
    CHECK(path == "path/to/file/file.txt");

    ChangeFilename(path, "file");
    CHECK(path == "path/to/file/file");

    ChangeFilename(path, "");
    CHECK(path == "path/to/file/");

    ChangeFilename(path, "other-file.doc");
    CHECK(path == "path/to/file/other-file.doc");
}

TEST_CASE("Get extension from path - without separator")
{
    using namespace Graphyte::Storage;

    CHECK(GetExtension(".txt", false) == "txt");
    CHECK(GetExtension("", false) == "");
    CHECK(GetExtension("/.txt", false) == "txt");
    CHECK(GetExtension("/", false) == "");
    CHECK(GetExtension("/file.txt", false) == "txt");
    CHECK(GetExtension("/file", false) == "");
    CHECK(GetExtension("file.txt", false) == "txt");
    CHECK(GetExtension("file", false) == "");
    CHECK(GetExtension("path/.txt", false) == "txt");
    CHECK(GetExtension("path/", false) == "");
    CHECK(GetExtension("path/file.txt", false) == "txt");
    CHECK(GetExtension("path/file", false) == "");
}

TEST_CASE("Get extension from path - with separator")
{
    using namespace Graphyte::Storage;

    CHECK(GetExtension(".txt", true) == ".txt");
    CHECK(GetExtension("", true) == "");
    CHECK(GetExtension("/.txt", true) == ".txt");
    CHECK(GetExtension("/", true) == "");
    CHECK(GetExtension("/file.txt", true) == ".txt");
    CHECK(GetExtension("/file", true) == "");
    CHECK(GetExtension("file.txt", true) == ".txt");
    CHECK(GetExtension("file", true) == "");
    CHECK(GetExtension("path/.txt", true) == ".txt");
    CHECK(GetExtension("path/", true) == "");
    CHECK(GetExtension("path/file.txt", true) == ".txt");
    CHECK(GetExtension("path/file", true) == "");
}

TEST_CASE("Get filename from path")
{
    using namespace Graphyte::Storage;

    CHECK(GetFilename(".txt") == ".txt");
    CHECK(GetFilename("") == "");
    CHECK(GetFilename("/.txt") == ".txt");
    CHECK(GetFilename("/") == "");
    CHECK(GetFilename("/file.txt") == "file.txt");
    CHECK(GetFilename("/file") == "file");
    CHECK(GetFilename("file.txt") == "file.txt");
    CHECK(GetFilename("file") == "file");
    CHECK(GetFilename("path/.txt") == ".txt");
    CHECK(GetFilename("path/") == "");
    CHECK(GetFilename("path/file.txt") == "file.txt");
    CHECK(GetFilename("path/file") == "file");
}

TEST_CASE("Get basename from path")
{
    using namespace Graphyte::Storage;

    CHECK(GetBaseFilename(".txt") == "");
    CHECK(GetBaseFilename("") == "");
    CHECK(GetBaseFilename("/.txt") == "");
    CHECK(GetBaseFilename("/") == "");
    CHECK(GetBaseFilename("/file.txt") == "file");
    CHECK(GetBaseFilename("/file") == "file");
    CHECK(GetBaseFilename("file.txt") == "file");
    CHECK(GetBaseFilename("file") == "file");
    CHECK(GetBaseFilename("path/.txt") == "");
    CHECK(GetBaseFilename("path/") == "");
    CHECK(GetBaseFilename("path/file.txt") == "file");
    CHECK(GetBaseFilename("path/file") == "file");
}

TEST_CASE("Get path from path")
{
    using namespace Graphyte::Storage;

    CHECK(GetPath(".txt") == "");
    CHECK(GetPath("") == "");
    CHECK(GetPath("/.txt") == "/");
    CHECK(GetPath("/") == "/");
    CHECK(GetPath("/file.txt") == "/");
    CHECK(GetPath("/file") == "/");
    CHECK(GetPath("file.txt") == "");
    CHECK(GetPath("file") == "");
    CHECK(GetPath("path/.txt") == "path/");
    CHECK(GetPath("path/") == "path/");
    CHECK(GetPath("path/file.txt") == "path/");
    CHECK(GetPath("path/file") == "path/");
}

TEST_CASE("Get path scheme")
{
    using namespace Graphyte::Storage;

    CHECK(GetScheme(".txt") == "");
    CHECK(GetScheme("") == "");
    CHECK(GetScheme(".") == "");
    CHECK(GetScheme("./base") == "");
    CHECK(GetScheme("/base") == "");
    CHECK(GetScheme("/./base") == "");
    CHECK(GetScheme("file://.") == "file");
    CHECK(GetScheme("dev://base/path") == "dev");
    CHECK(GetScheme("d:/file/name") == "");
    CHECK(GetScheme("http://google.com") == "http");
}

TEST_CASE("Normalize path")
{
    using namespace Graphyte::Storage;

    CHECK(NormalizedPath(".txt") == ".txt");
    CHECK(NormalizedPath("") == "");
    CHECK(NormalizedPath("/.txt") == "/.txt");
    CHECK(NormalizedPath("/") == "/");
    CHECK(NormalizedPath("/file.txt") == "/file.txt");
    CHECK(NormalizedPath("/file") == "/file");
    CHECK(NormalizedPath("\\.txt") == "/.txt");
    CHECK(NormalizedPath("\\") == "/");
    CHECK(NormalizedPath("\\file.txt") == "/file.txt");
    CHECK(NormalizedPath("\\file") == "/file");
    CHECK(NormalizedPath("file.txt") == "file.txt");
    CHECK(NormalizedPath("file") == "file");
    CHECK(NormalizedPath("path/.txt") == "path/.txt");
    CHECK(NormalizedPath("path/") == "path/");
    CHECK(NormalizedPath("path/file.txt") == "path/file.txt");
    CHECK(NormalizedPath("path/file") == "path/file");
    CHECK(NormalizedPath("path\\.txt") == "path/.txt");
    CHECK(NormalizedPath("path\\") == "path/");
    CHECK(NormalizedPath("path\\file.txt") == "path/file.txt");
    CHECK(NormalizedPath("path\\file") == "path/file");
}

TEST_CASE("Collapse paths")
{
    using namespace Graphyte::Storage;

    SECTION("Checking one")
    {
        std::string path{ "/some/base/long/path/with/multiple/../../../../relative/subpath" };
        CHECK(CanonicalizePath(path));
        CHECK(path == "/some/base/relative/subpath");
    }
    SECTION("Checking one")
    {
        std::string path{ "" };
        CHECK(CanonicalizePath(path));
        CHECK(path == "");
    }
    SECTION("Checking one")
    {
        std::string path{ ".." };
        CHECK(CanonicalizePath(path) == false);
        CHECK(path == "..");
    }
    SECTION("Checking one")
    {
        std::string path{ "/.." };
        CHECK(CanonicalizePath(path) == false);
        CHECK(path == "/..");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base" };
        CHECK(CanonicalizePath(path));
        CHECK(path == "/base");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base/path" };
        CHECK(CanonicalizePath(path));
        CHECK(path == "/base/path");
    }
    SECTION("Checking one")
    {
        std::string path{ "./base/path" };
        CHECK(CanonicalizePath(path));
        CHECK(path == "base/path");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base/./path" };
        CHECK(CanonicalizePath(path));
        CHECK(path == "/base/path");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base/../path" };
        CHECK(CanonicalizePath(path));
        CHECK(path == "/path");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base/./../path/to/something/../." };
        CHECK(CanonicalizePath(path));
        CHECK(path == "/path/to/.");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base/././././././././path/../to/something/../../other/than/rest" };
        CHECK(CanonicalizePath(path));
        CHECK(path == "/base/other/than/rest");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base/......../path" };
        CHECK(CanonicalizePath(path) == false);
        CHECK(path == "....../path");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base/path/./to/../something" };
        CHECK(CanonicalizePath(path));
        CHECK(path == "/base/path/something");
    }
    SECTION("Checking one")
    {
        std::string path{ "../../../path/invalid" };
        CHECK(CanonicalizePath(path) == false);
        CHECK(path == "../../../path/invalid");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base/path/to/relative/../other/./path" };
        CHECK(CanonicalizePath(path));
        CHECK(path == "/base/path/to/other/path");
    }
}

TEST_CASE("Relative paths")
{
    using namespace Graphyte::Storage;

    std::string result{};

    CHECK(RelativePath(result, "c:\\a\\b\\path", "c:\\a\\x\\y\\file"));
    CHECK(result == "../../x/y/file");

    CHECK(RelativePath(result, "c:\\a\\b\\path", "d:\\a\\x\\y\\file") == false);

    CHECK(RelativePath(result, "/base/path/to/somewhere", "/base/somewhere/else"));
    CHECK(result == "../../../somewhere/else");

    CHECK(RelativePath(result, "C:/Users/noname/Documents/", "C:/Users/noname/Documents/SomeGame(TM)/out/Settings/Video.scr"));
    CHECK(result == "SomeGame(TM)/out/Settings/Video.scr");
}
