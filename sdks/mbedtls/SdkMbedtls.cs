using Neobyte.Build.Framework;
using System.IO;

namespace Graphyte
{
    [ModuleRules]
    public class SdkMbedtls
        : ModuleRules
    {
        public SdkMbedtls(TargetRules target)
            : base(target)
        {
            this.Type = ModuleType.StaticLibrary;
            this.Kind = ModuleKind.ThirdParty;
            this.Language = ModuleLanguage.C;

            this.PublicIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "include"));

            if (target.Descriptor.Architecture == TargetArchitecture.X64)
            {
                this.PrivateDefines.Add("MBEDTLS_HAVE_SSE2=1");
            }
        }
    }
}

#if false
"library/aes.c",
"library/aesni.c",
"library/arc4.c",
"library/aria.c",
"library/asn1parse.c",
"library/asn1write.c",
"library/base64.c",
"library/bignum.c",
"library/blowfish.c",
"library/camellia.c",
"library/ccm.c",
"library/certs.c",
"library/chacha20.c",
"library/chachapoly.c",
"library/cipher.c",
"library/cipher_wrap.c",
"library/cmac.c",
"library/ctr_drbg.c",
"library/des.c",
"library/dhm.c",
"library/ecdh.c",
"library/ecdsa.c",
"library/ecjpake.c",
"library/ecp.c",
"library/ecp_curves.c",
"library/entropy.c",
"library/entropy_poll.c",
"library/error.c",
"library/gcm.c",
"library/havege.c",
"library/hkdf.c",
"library/hmac_drbg.c",
"library/md.c",
"library/md2.c",
"library/md4.c",
"library/md5.c",
"library/md_wrap.c",
"library/memory_buffer_alloc.c",
"library/net_sockets.c",
"library/nist_kw.c",
"library/oid.c",
"library/padlock.c",
"library/pem.c",
"library/pk.c",
"library/pkcs11.c",
"library/pkcs12.c",
"library/pkcs5.c",
"library/pkparse.c",
"library/pkwrite.c",
"library/pk_wrap.c",
"library/platform.c",
"library/platform_util.c",
"library/poly1305.c",
"library/ripemd160.c",
"library/rsa.c",
"library/rsa_internal.c",
"library/sha1.c",
"library/sha256.c",
"library/sha512.c",
"library/ssl_cache.c",
"library/ssl_ciphersuites.c",
"library/ssl_cli.c",
"library/ssl_cookie.c",
"library/ssl_srv.c",
"library/ssl_ticket.c",
"library/ssl_tls.c",
"library/threading.c",
"library/timing.c",
"library/version.c",
"library/version_features.c",
"library/x509.c",
"library/x509write_crt.c",
"library/x509write_csr.c",
"library/x509_create.c",
"library/x509_crl.c",
"library/x509_crt.c",
"library/x509_csr.c",
"library/xtea.c",
#endif
