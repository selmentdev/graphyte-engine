//         internal void ImplResolveProperties(ResolveContext context)
//         {
//             // Resolve all properties

//             // public includes
//             var allPublicIncludes = this.PublicIncludes.Concat(this.ResolvedInheritedDependencies.SelectMany(x => x.PublicIncludes));
//             foreach (var include in allPublicIncludes)
//             {
//                 if (!this.ResolvedPublicIncludes.Contains(include))
//                 {
//                     this.ResolvedPublicIncludes.Add(include);
//                 }
//             }
//             var allPrivateIncludes = this.PrivateIncludes;
//             foreach (var include in allPrivateIncludes)
//             {
//                 if (!this.ResolvedPrivateIncludes.Contains(include))
//                 {
//                     this.ResolvedPrivateIncludes.Add(include);
//                 }
//             }

//             var allLibraries = this.Libraries.Concat(this.ResolvedInheritedDependencies.SelectMany(x => x.Libraries));
//             foreach (var include in allLibraries)
//             {
//                 if (!this.ResolvedLibraries.Contains(include))
//                 {
//                     this.ResolvedLibraries.Add(include);
//                 }
//             }

//             var allPublicDefines = this.PublicDefines.Concat(this.ResolvedInheritedDependencies.SelectMany(x => x.PublicDefines));
//             foreach (var define in allPublicDefines)
//             {
//                 if (!this.ResolvedPublicDefines.ContainsKey(define.Key))
//                 {
//                     this.ResolvedPublicDefines.Add(define.Key, define.Value);
//                 }
//             }

//             var allPrivateDefines = this.PrivateDefines;
//             foreach (var define in allPrivateDefines)
//             {
//                 if (!this.ResolvedPrivateDefines.ContainsKey(define.Key))
//                 {
//                     this.ResolvedPrivateDefines.Add(define.Key, define.Value);
//                 }
//             }
//         }

//         public string? ExportSymbol
//         {
//             get
//             {
//                 if (this.Kind == ProjectKind.SharedLib)
//                 {
//                     return $@"module_export_{this.Name}";
//                 }

//                 return null;

//             }
//         }
