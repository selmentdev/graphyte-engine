#include <catch2/catch.hpp>
#include <GxBase/Storage/Path.hxx>

using Graphyte::Storage::Path;

TEST_CASE("Path appending")
{
    std::string path{};
    CHECK(path == "");

    Path::Append(path, "root");
    CHECK(path == "root");

    Path::Append(path, "game");
    CHECK(path == "root/game");

    Path::Append(path, "assets");
    CHECK(path == "root/game/assets");

    Path::Append(path, "meshes");
    CHECK(path == "root/game/assets/meshes");

    Path::Append(path, "package");
    CHECK(path == "root/game/assets/meshes/package");

    Path::Append(path, "main.mesh");
    CHECK(path == "root/game/assets/meshes/package/main.mesh");

    Path::Append(path, "");
    CHECK(path == "root/game/assets/meshes/package/main.mesh");

    Path::Append(path, "");
    CHECK(path == "root/game/assets/meshes/package/main.mesh");

    Path::Append(path, "");
    CHECK(path == "root/game/assets/meshes/package/main.mesh");

    Path::Append(path, "subname/after/filename.html");
    CHECK(path == "root/game/assets/meshes/package/main.mesh/subname/after/filename.html");
}

TEST_CASE("Path appending - denegerated cases")
{
    std::string result{ "app.demo" };

    Path::Append(result, "../../");
    CHECK(result == "app.demo/../../");

    REQUIRE(Path::Canonicalize(result));
    REQUIRE(result == "app.demo/..");
}

TEST_CASE("Path combining")
{
    CHECK(Path::Combine("root", "game") == "root/game");
    CHECK(Path::Combine("root", "game", "assets") == "root/game/assets");
    CHECK(Path::Combine("root", "game", "assets", "meshes") == "root/game/assets/meshes");
    CHECK(Path::Combine("root", "game", "assets", "meshes", "package") == "root/game/assets/meshes/package");
    CHECK(Path::Combine("root", "game", "assets", "meshes", "package", "main.mesh") == "root/game/assets/meshes/package/main.mesh");
}

TEST_CASE("Changing extension - empty path")
{
    std::string path = "";

    Path::ChangeExtension(path, ".txt");
    CHECK(path == ".txt");

    Path::ChangeExtension(path, ".ref");
    CHECK(path == ".ref");

    Path::ChangeExtension(path, "");
    CHECK(path == "");

    Path::ChangeExtension(path, "txt");
    CHECK(path == ".txt");

    Path::ChangeExtension(path, "wtf");
    CHECK(path == ".wtf");
}

TEST_CASE("Changing extension - simple filename path")
{
    std::string path = "file";

    Path::ChangeExtension(path, ".txt");
    CHECK(path == "file.txt");

    Path::ChangeExtension(path, ".ref");
    CHECK(path == "file.ref");

    Path::ChangeExtension(path, "");
    CHECK(path == "file");

    Path::ChangeExtension(path, "txt");
    CHECK(path == "file.txt");

    Path::ChangeExtension(path, "wtf");
    CHECK(path == "file.wtf");
}

TEST_CASE("Changing extension - simple filename path with base path")
{
    std::string path = "some/path/to/file";

    Path::ChangeExtension(path, ".txt");
    CHECK(path == "some/path/to/file.txt");

    Path::ChangeExtension(path, ".ref");
    CHECK(path == "some/path/to/file.ref");

    Path::ChangeExtension(path, "");
    CHECK(path == "some/path/to/file");

    Path::ChangeExtension(path, "txt");
    CHECK(path == "some/path/to/file.txt");

    Path::ChangeExtension(path, "wtf");
    CHECK(path == "some/path/to/file.wtf");
}

TEST_CASE("Changing extension - simple filename + extension path with base path")
{
    std::string path = "some/path/to/file.cxx";

    Path::ChangeExtension(path, ".txt");
    CHECK(path == "some/path/to/file.txt");

    Path::ChangeExtension(path, ".ref");
    CHECK(path == "some/path/to/file.ref");

    Path::ChangeExtension(path, "");
    CHECK(path == "some/path/to/file");

    Path::ChangeExtension(path, "txt");
    CHECK(path == "some/path/to/file.txt");

    Path::ChangeExtension(path, "wtf");
    CHECK(path == "some/path/to/file.wtf");
}

TEST_CASE("Changing file name - empty path")
{
    std::string path = "";

    Path::ChangeFilename(path, "file.txt");
    CHECK(path == "file.txt");

    Path::ChangeFilename(path, "file");
    CHECK(path == "file");

    Path::ChangeFilename(path, "");
    CHECK(path == "");

    Path::ChangeFilename(path, "other-file.doc");
    CHECK(path == "other-file.doc");
}

TEST_CASE("Changing file name - just file name")
{
    std::string path = "main";

    Path::ChangeFilename(path, "file.txt");
    CHECK(path == "file.txt");

    Path::ChangeFilename(path, "file");
    CHECK(path == "file");

    Path::ChangeFilename(path, "");
    CHECK(path == "");

    Path::ChangeFilename(path, "other-file.doc");
    CHECK(path == "other-file.doc");
}

TEST_CASE("Changing file name - just file name with extension")
{
    std::string path = "main";

    Path::ChangeFilename(path, "file.txt");
    CHECK(path == "file.txt");

    Path::ChangeFilename(path, "file");
    CHECK(path == "file");

    Path::ChangeFilename(path, "");
    CHECK(path == "");

    Path::ChangeFilename(path, "other-file.doc");
    CHECK(path == "other-file.doc");
}

TEST_CASE("Changing file name - just path")
{
    std::string path = "path/to/file/";

    Path::ChangeFilename(path, "file.txt");
    CHECK(path == "path/to/file/file.txt");

    Path::ChangeFilename(path, "file");
    CHECK(path == "path/to/file/file");

    Path::ChangeFilename(path, "");
    CHECK(path == "path/to/file/");

    Path::ChangeFilename(path, "other-file.doc");
    CHECK(path == "path/to/file/other-file.doc");
}

TEST_CASE("Changing file name - path with file name")
{
    std::string path = "path/to/file/other.html";

    Path::ChangeFilename(path, "file.txt");
    CHECK(path == "path/to/file/file.txt");

    Path::ChangeFilename(path, "file");
    CHECK(path == "path/to/file/file");

    Path::ChangeFilename(path, "");
    CHECK(path == "path/to/file/");

    Path::ChangeFilename(path, "other-file.doc");
    CHECK(path == "path/to/file/other-file.doc");
}

TEST_CASE("Get extension from path - without separator")
{
    CHECK(Path::GetExtension(".txt", false) == "txt");
    CHECK(Path::GetExtension("", false) == "");
    CHECK(Path::GetExtension("/.txt", false) == "txt");
    CHECK(Path::GetExtension("/", false) == "");
    CHECK(Path::GetExtension("/file.txt", false) == "txt");
    CHECK(Path::GetExtension("/file", false) == "");
    CHECK(Path::GetExtension("file.txt", false) == "txt");
    CHECK(Path::GetExtension("file", false) == "");
    CHECK(Path::GetExtension("path/.txt", false) == "txt");
    CHECK(Path::GetExtension("path/", false) == "");
    CHECK(Path::GetExtension("path/file.txt", false) == "txt");
    CHECK(Path::GetExtension("path/file", false) == "");
}

TEST_CASE("Get extension from path - with separator")
{
    CHECK(Path::GetExtension(".txt", true) == ".txt");
    CHECK(Path::GetExtension("", true) == "");
    CHECK(Path::GetExtension("/.txt", true) == ".txt");
    CHECK(Path::GetExtension("/", true) == "");
    CHECK(Path::GetExtension("/file.txt", true) == ".txt");
    CHECK(Path::GetExtension("/file", true) == "");
    CHECK(Path::GetExtension("file.txt", true) == ".txt");
    CHECK(Path::GetExtension("file", true) == "");
    CHECK(Path::GetExtension("path/.txt", true) == ".txt");
    CHECK(Path::GetExtension("path/", true) == "");
    CHECK(Path::GetExtension("path/file.txt", true) == ".txt");
    CHECK(Path::GetExtension("path/file", true) == "");
}

TEST_CASE("Get filename from path")
{
    CHECK(Path::GetFilename(".txt") == ".txt");
    CHECK(Path::GetFilename("") == "");
    CHECK(Path::GetFilename("/.txt") == ".txt");
    CHECK(Path::GetFilename("/") == "");
    CHECK(Path::GetFilename("/file.txt") == "file.txt");
    CHECK(Path::GetFilename("/file") == "file");
    CHECK(Path::GetFilename("file.txt") == "file.txt");
    CHECK(Path::GetFilename("file") == "file");
    CHECK(Path::GetFilename("path/.txt") == ".txt");
    CHECK(Path::GetFilename("path/") == "");
    CHECK(Path::GetFilename("path/file.txt") == "file.txt");
    CHECK(Path::GetFilename("path/file") == "file");
}

TEST_CASE("Get basename from path")
{
    CHECK(Path::GetBaseFilename(".txt") == "");
    CHECK(Path::GetBaseFilename("") == "");
    CHECK(Path::GetBaseFilename("/.txt") == "");
    CHECK(Path::GetBaseFilename("/") == "");
    CHECK(Path::GetBaseFilename("/file.txt") == "file");
    CHECK(Path::GetBaseFilename("/file") == "file");
    CHECK(Path::GetBaseFilename("file.txt") == "file");
    CHECK(Path::GetBaseFilename("file") == "file");
    CHECK(Path::GetBaseFilename("path/.txt") == "");
    CHECK(Path::GetBaseFilename("path/") == "");
    CHECK(Path::GetBaseFilename("path/file.txt") == "file");
    CHECK(Path::GetBaseFilename("path/file") == "file");
}

TEST_CASE("Get path from path")
{
    CHECK(Path::GetPath(".txt") == "");
    CHECK(Path::GetPath("") == "");
    CHECK(Path::GetPath("/.txt") == "/");
    CHECK(Path::GetPath("/") == "/");
    CHECK(Path::GetPath("/file.txt") == "/");
    CHECK(Path::GetPath("/file") == "/");
    CHECK(Path::GetPath("file.txt") == "");
    CHECK(Path::GetPath("file") == "");
    CHECK(Path::GetPath("path/.txt") == "path/");
    CHECK(Path::GetPath("path/") == "path/");
    CHECK(Path::GetPath("path/file.txt") == "path/");
    CHECK(Path::GetPath("path/file") == "path/");
}

TEST_CASE("Get path scheme")
{
    CHECK(Path::GetScheme(".txt") == "");
    CHECK(Path::GetScheme("") == "");
    CHECK(Path::GetScheme(".") == "");
    CHECK(Path::GetScheme("./base") == "");
    CHECK(Path::GetScheme("/base") == "");
    CHECK(Path::GetScheme("/./base") == "");
    CHECK(Path::GetScheme("file://.") == "file");
    CHECK(Path::GetScheme("dev://base/path") == "dev");
    CHECK(Path::GetScheme("d:/file/name") == "");
    CHECK(Path::GetScheme("http://google.com") == "http");
}

TEST_CASE("Get extension from path - without separator - reference")
{
    CHECK(Path::GetExtensionRef(".txt", false) == "txt");
    CHECK(Path::GetExtensionRef("", false) == "");
    CHECK(Path::GetExtensionRef("/.txt", false) == "txt");
    CHECK(Path::GetExtensionRef("/", false) == "");
    CHECK(Path::GetExtensionRef("/file.txt", false) == "txt");
    CHECK(Path::GetExtensionRef("/file", false) == "");
    CHECK(Path::GetExtensionRef("file.txt", false) == "txt");
    CHECK(Path::GetExtensionRef("file", false) == "");
    CHECK(Path::GetExtensionRef("path/.txt", false) == "txt");
    CHECK(Path::GetExtensionRef("path/", false) == "");
    CHECK(Path::GetExtensionRef("path/file.txt", false) == "txt");
    CHECK(Path::GetExtensionRef("path/file", false) == "");
}

TEST_CASE("Get extension from path - with separator - reference")
{
    CHECK(Path::GetExtensionRef(".txt", true) == ".txt");
    CHECK(Path::GetExtensionRef("", true) == "");
    CHECK(Path::GetExtensionRef("/.txt", true) == ".txt");
    CHECK(Path::GetExtensionRef("/", true) == "");
    CHECK(Path::GetExtensionRef("/file.txt", true) == ".txt");
    CHECK(Path::GetExtensionRef("/file", true) == "");
    CHECK(Path::GetExtensionRef("file.txt", true) == ".txt");
    CHECK(Path::GetExtensionRef("file", true) == "");
    CHECK(Path::GetExtensionRef("path/.txt", true) == ".txt");
    CHECK(Path::GetExtensionRef("path/", true) == "");
    CHECK(Path::GetExtensionRef("path/file.txt", true) == ".txt");
    CHECK(Path::GetExtensionRef("path/file", true) == "");
}

TEST_CASE("Get filename from path - reference")
{
    CHECK(Path::GetFilenameRef(".txt") == ".txt");
    CHECK(Path::GetFilenameRef("") == "");
    CHECK(Path::GetFilenameRef("/.txt") == ".txt");
    CHECK(Path::GetFilenameRef("/") == "");
    CHECK(Path::GetFilenameRef("/file.txt") == "file.txt");
    CHECK(Path::GetFilenameRef("/file") == "file");
    CHECK(Path::GetFilenameRef("file.txt") == "file.txt");
    CHECK(Path::GetFilenameRef("file") == "file");
    CHECK(Path::GetFilenameRef("path/.txt") == ".txt");
    CHECK(Path::GetFilenameRef("path/") == "");
    CHECK(Path::GetFilenameRef("path/file.txt") == "file.txt");
    CHECK(Path::GetFilenameRef("path/file") == "file");
}

TEST_CASE("Get basename from path - reference")
{
    CHECK(Path::GetBaseFilenameRef(".txt") == "");
    CHECK(Path::GetBaseFilenameRef("") == "");
    CHECK(Path::GetBaseFilenameRef("/.txt") == "");
    CHECK(Path::GetBaseFilenameRef("/") == "");
    CHECK(Path::GetBaseFilenameRef("/file.txt") == "file");
    CHECK(Path::GetBaseFilenameRef("/file") == "file");
    CHECK(Path::GetBaseFilenameRef("file.txt") == "file");
    CHECK(Path::GetBaseFilenameRef("file") == "file");
    CHECK(Path::GetBaseFilenameRef("path/.txt") == "");
    CHECK(Path::GetBaseFilenameRef("path/") == "");
    CHECK(Path::GetBaseFilenameRef("path/file.txt") == "file");
    CHECK(Path::GetBaseFilenameRef("path/file") == "file");
}

TEST_CASE("Get path from path - reference")
{
    CHECK(Path::GetPathRef(".txt") == "");
    CHECK(Path::GetPathRef("") == "");
    CHECK(Path::GetPathRef("/.txt") == "/");
    CHECK(Path::GetPathRef("/") == "/");
    CHECK(Path::GetPathRef("/file.txt") == "/");
    CHECK(Path::GetPathRef("/file") == "/");
    CHECK(Path::GetPathRef("file.txt") == "");
    CHECK(Path::GetPathRef("file") == "");
    CHECK(Path::GetPathRef("path/.txt") == "path/");
    CHECK(Path::GetPathRef("path/") == "path/");
    CHECK(Path::GetPathRef("path/file.txt") == "path/");
    CHECK(Path::GetPathRef("path/file") == "path/");
}

TEST_CASE("Get path scheme - reference")
{
    CHECK(Path::GetSchemeRef(".txt") == "");
    CHECK(Path::GetSchemeRef("") == "");
    CHECK(Path::GetSchemeRef(".") == "");
    CHECK(Path::GetSchemeRef("./base") == "");
    CHECK(Path::GetSchemeRef("/base") == "");
    CHECK(Path::GetSchemeRef("/./base") == "");
    CHECK(Path::GetSchemeRef("file://.") == "file");
    CHECK(Path::GetSchemeRef("dev://base/path") == "dev");
    CHECK(Path::GetSchemeRef("d:/file/name") == "");
    CHECK(Path::GetSchemeRef("http://google.com") == "http");
}

TEST_CASE("Normalize path")
{
    CHECK(Path::Normalized(".txt") == ".txt");
    CHECK(Path::Normalized("") == "");
    CHECK(Path::Normalized("/.txt") == "/.txt");
    CHECK(Path::Normalized("/") == "/");
    CHECK(Path::Normalized("/file.txt") == "/file.txt");
    CHECK(Path::Normalized("/file") == "/file");
    CHECK(Path::Normalized("\\.txt") == "/.txt");
    CHECK(Path::Normalized("\\") == "/");
    CHECK(Path::Normalized("\\file.txt") == "/file.txt");
    CHECK(Path::Normalized("\\file") == "/file");
    CHECK(Path::Normalized("file.txt") == "file.txt");
    CHECK(Path::Normalized("file") == "file");
    CHECK(Path::Normalized("path/.txt") == "path/.txt");
    CHECK(Path::Normalized("path/") == "path/");
    CHECK(Path::Normalized("path/file.txt") == "path/file.txt");
    CHECK(Path::Normalized("path/file") == "path/file");
    CHECK(Path::Normalized("path\\.txt") == "path/.txt");
    CHECK(Path::Normalized("path\\") == "path/");
    CHECK(Path::Normalized("path\\file.txt") == "path/file.txt");
    CHECK(Path::Normalized("path\\file") == "path/file");
}

TEST_CASE("Collapse paths")
{
    SECTION("Checking one")
    {
        std::string path{ "/some/base/long/path/with/multiple/../../../../relative/subpath" };
        CHECK(Path::Canonicalize(path));
        CHECK(path == "/some/base/relative/subpath");
    }
    SECTION("Checking one")
    {
        std::string path{ "" };
        CHECK(Path::Canonicalize(path));
        CHECK(path == "");
    }
    SECTION("Checking one")
    {
        std::string path{ ".." };
        CHECK(Path::Canonicalize(path) == false);
        CHECK(path == "..");
    }
    SECTION("Checking one")
    {
        std::string path{ "/.." };
        CHECK(Path::Canonicalize(path) == false);
        CHECK(path == "/..");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base" };
        CHECK(Path::Canonicalize(path));
        CHECK(path == "/base");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base/path" };
        CHECK(Path::Canonicalize(path));
        CHECK(path == "/base/path");
    }
    SECTION("Checking one")
    {
        std::string path{ "./base/path" };
        CHECK(Path::Canonicalize(path));
        CHECK(path == "base/path");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base/./path" };
        CHECK(Path::Canonicalize(path));
        CHECK(path == "/base/path");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base/../path" };
        CHECK(Path::Canonicalize(path));
        CHECK(path == "/path");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base/./../path/to/something/../." };
        CHECK(Path::Canonicalize(path));
        CHECK(path == "/path/to/.");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base/././././././././path/../to/something/../../other/than/rest" };
        CHECK(Path::Canonicalize(path));
        CHECK(path == "/base/other/than/rest");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base/......../path" };
        CHECK(Path::Canonicalize(path) == false);
        CHECK(path == "....../path");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base/path/./to/../something" };
        CHECK(Path::Canonicalize(path));
        CHECK(path == "/base/path/something");
    }
    SECTION("Checking one")
    {
        std::string path{ "../../../path/invalid" };
        CHECK(Path::Canonicalize(path) == false);
        CHECK(path == "../../../path/invalid");
    }
    SECTION("Checking one")
    {
        std::string path{ "/base/path/to/relative/../other/./path" };
        CHECK(Path::Canonicalize(path));
        CHECK(path == "/base/path/to/other/path");
    }
}

TEST_CASE("Relative paths")
{
    std::string result{};

    CHECK(Path::Relative(result, "c:\\a\\b\\path", "c:\\a\\x\\y\\file"));
    CHECK(result == "../../x/y/file");

    CHECK(Path::Relative(result, "c:\\a\\b\\path", "d:\\a\\x\\y\\file") == false);

    CHECK(Path::Relative(result, "/base/path/to/somewhere", "/base/somewhere/else"));
    CHECK(result == "../../../somewhere/else");

    CHECK(Path::Relative(result, "C:/Users/noname/Documents/", "C:/Users/noname/Documents/SomeGame(TM)/out/Settings/Video.scr"));
    CHECK(result == "SomeGame(TM)/out/Settings/Video.scr");
}
