auth_request /auth_verify;

auth_request_set $user      $upstream_http_remote_user;
proxy_set_header            X-Forwarded-User $user;

auth_request_set            $groups $upstream_http_remote_groups;
proxy_set_header            Remote-Groups $groups;

# Route the request to the correct virtual host in the backend.
proxy_set_header            Host $http_host;

# Authelia relies on Proxy-Authorization header to authenticate in basic auth.
# but for the sake of simplicity (because Authorization in supported in most
# clients) we take Authorization from the frontend and rewrite it to
# Proxy-Authorization before sending it to Authelia.
proxy_set_header            Proxy-Authorization $http_authorization;

# mitigate HTTPoxy Vulnerability
# https://www.nginx.com/blog/mitigating-the-httpoxy-vulnerability-with-nginx/
proxy_set_header            Proxy "";

# Set the `target_url` variable based on the request. It will be used to build the portal
# URL with the correct redirection parameter.
set                         $target_url $scheme://$http_host$request_uri;
error_page 401 =302         https://auth.mydomain.com/?rd=$target_url;
